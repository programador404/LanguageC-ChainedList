#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct dataNode {
	int id;
} DataNode;

typedef struct node {
	DataNode data;
	struct node* next;
}Node;

typedef struct list {
	int size;
	Node* head;
} List;

List* createList();
void pushList(List* list, DataNode data);
bool isEmpityList(List* list);
void printList(List* list);
void popList(List* list);
Node* positionOnList(List* list, int index);
int indexOfList(List* list, Node* node);
void eraseValueOnList(List* list, int index);
void insertList(List* list, DataNode data, int index);
void xchgNode(List* list, Node* nodeA, Node* nodeB);
Node* minimumNodeList(List* list, int index);
Node* maximumNodeList(List* list, int index);

List* createList() {
	List* list = (List*) malloc(sizeof(List));

	list->size = 0;
	list->head = NULL;
		
	return list;
}

void pushList(List* list, DataNode data) {
	Node* node = (Node*) malloc(sizeof(Node));

	node->data = data;
	node->next = list->head;
	list->head = node;
	list->size++;
}

bool isEmpityList(List* list) {
	return (list->size == 0);
};

void printList(List* list) {
	if (isEmpityList(list)) {
		printf("List Empity\n");
	}

	Node* pointer = list->head;

	while (pointer != NULL) {
		printf("%d ", pointer->data.id);
		pointer = pointer->next;
	}

	printf("\n");
}

void popList(List* list) {
	if (!isEmpityList(list)) {
		Node* pointer = list->head;
		list->head = pointer->next;
		free(pointer);
		list->size--;
	}
};

Node* positionOnList(List* list, int index) {
	if (index >= 0 && index < list->size) {
		Node* pointer = list->head;

		int iterator;
		for (iterator = 0; iterator < index; iterator++) {
			pointer = pointer->next;
		}

		return pointer;
	}

	printf("Invalid Index");
	return NULL;
}

int indexOfList(List* list, Node* node) {
	if (node != NULL) {
		Node* pointer = list->head;
		int index = 0;

		while (pointer != node && pointer != NULL) {
			pointer = pointer->next;
			index++;
		}

		if (pointer != NULL)
			return index;
	}

	printf("Invalid Node");
	return NULL;
}

void eraseValueOnList(List* list, int index) {
	if (index == 0) {
		popList(list);
	}
	else {
		Node* currentNode = positionOnList(list, index);

		if (currentNode != NULL) {
			Node* previousNode = positionOnList(list, index - 1);
			previousNode->next = currentNode->next;

			free(currentNode);
			list->size--;
		}
	}
}

void insertList(List* list, DataNode data, int index) {
	if (index == 0) {
		pushList(list, data);
	}
	else {
		Node* currentNode = positionOnList(list, index);
		if (currentNode != NULL) {
			Node* previousNode = positionOnList(list, index - 1);

			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->data = data;

			previousNode->next = newNode;
			newNode->next = currentNode;
			list->size++;
		}
	}
}

void xchgNode(List* list, Node* nodeA, Node* nodeB) {
	if (nodeA == nodeB)
		return;

	int indexA = indexOfList(list, nodeA);
	int indexB = indexOfList(list, nodeB);

	if (indexA == -1 || indexB == -1)
		return;

	if (indexA > indexB) {
		nodeA = nodeB;
		nodeB = positionOnList(list, indexA);

		indexA = indexB;
		indexB = indexOfList(list, nodeB);
	}

	Node* pb = positionOnList(list, indexB - 1);

	if (nodeA == list->head) {
		list->head = nodeB;
	}
	else {
		Node* pa = positionOnList(list, indexA - 1);
		pa->next = nodeB;
	}

	pb->next = nodeA;

	Node* pointerNextNodeA = nodeA->next;
	nodeA->next = nodeB->next;
	nodeB->next = pointerNextNodeA;
}

Node* minimumNodeList(List* list, int index) {
	Node* pointer = positionOnList(list, index);
	
	if (pointer != NULL) {
		Node* minimunNode = pointer;

		while (pointer != NULL) {
			if (pointer->data.id < minimunNode->data.id) {
				minimunNode = pointer;
			}
			pointer = pointer->next;
		}

		return minimunNode;
	}

	return NULL;
}

Node* maximumNodeList(List* list, int index) {
	Node* pointer = positionOnList(list, index);

	if (pointer != NULL) {
		Node* maximumNode = pointer;

		while (pointer != NULL) {
			if (pointer->data.id > maximumNode->data.id) {
				maximumNode = pointer;
			}
			pointer = pointer->next;
		}

		return maximumNode;
	}

	return NULL;
}

int main() {
	setlocale(LC_ALL, "pt-br");

	List* newList = createList();
	DataNode data;

	data.id = 5;
	pushList(newList, data);
	data.id = 10;
	pushList(newList, data);
	data.id = 15;
	pushList(newList, data);
	data.id = 20;
	pushList(newList, data);

	printList(newList);
	popList(newList);
	printList(newList);
	eraseValueOnList(newList, 1);
	printList(newList);

	data.id = 25;
	insertList(newList, data, 1);
	printList(newList);

	Node* value = (Node*) positionOnList(newList, 1);
	int index = indexOfList(newList, value);

	printf("O id do valor na posição %d vale %d", index, value->data.id);

	return(0);
}