#include<stdio.h>
#include<stdlib.h>

// Terminal Colors just to heighlight the nodes .. and its data
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define RESET "\x1B[0m"

// Structure of a particular node ...
typedef struct node{
	
	int data;
	struct node *nextNode;
}SLLNode;

// Variable to be incremented on every new node added ...
int countNodes;

// Function that creates a indivisual node and assigns feilds of the node
SLLNode *createNode(int num){
	
	SLLNode *newNode = (SLLNode*)malloc(sizeof(SLLNode));
	newNode->nextNode = NULL;
	newNode->data = num;
	return newNode;
}

// At the time of Termination of program this function is called that will free the memory of heap  ...
void freeAllNodes(SLLNode **headNode){
	
	if (*headNode == NULL){return;}
	if ((*headNode)->nextNode == NULL)
		free(*headNode);
	else{
		while ((*headNode)->nextNode != NULL){
			SLLNode *freeNode = *headNode;
			*headNode = (*headNode)->nextNode;
			free(freeNode);
		}
	}


}

// This function will add a new Node to the end of the nodes ...
void addNewNode(SLLNode **headNode, int num){

	SLLNode *newNode = createNode(num);
	if (*headNode == NULL){
		*headNode = newNode;
		

	}else{
		SLLNode **dummyNode = headNode;
		while((*dummyNode)->nextNode != NULL){
			dummyNode = &(*dummyNode) -> nextNode;
	
		}
		(*dummyNode)->nextNode = newNode;
	}

	countNodes += 1;
}

// This function will search a particular element's second last
// occurence and return its position ...
int searchSecondLastOcc(SLLNode *headNode, int searchElem){
	
	int *positionArr;
	int *posArrTraversal;
	int posTracker = 1;
	int countOcc = 0;
	SLLNode *dummyNode = headNode, *countNodeOcc = headNode;

	for (int i = 0; countNodeOcc != NULL; i++){
		if (countNodeOcc -> data == searchElem)
			countOcc ++;
		countNodeOcc = countNodeOcc -> nextNode;
	}

	if (countOcc == 0)
		return -1;
	
	positionArr = (int*) malloc(countOcc * sizeof(int));
	posArrTraversal = positionArr;

	while (dummyNode != NULL){

		if (dummyNode -> data == searchElem )
			*(posArrTraversal++) = posTracker;

		posTracker += 1;
		dummyNode = dummyNode -> nextNode;
	}

	if (countOcc == 1)
		countOcc = *positionArr;
	else
		countOcc = *(positionArr + (countOcc-2));
	free(positionArr);
	positionArr = NULL;
	posArrTraversal = NULL;
	dummyNode = NULL;
	countNodeOcc = NULL;
	return countOcc;
	
}

// This function will display the list of all the created nodes ...
void displayNodes(SLLNode *headNode){

	SLLNode *dummyNode = headNode;
	while(dummyNode != NULL){
		printf("|\033[1;35mdata: %d \033[0m@\033[1;34m %p \033[0m| \033[1;36m->\033[0m "RESET,dummyNode->data, dummyNode->nextNode);
		dummyNode = dummyNode->nextNode;
	}
}


// Driver code containing a menu to display options ...
void main(void){

	int choice, data, position, retValue;
	SLLNode *headNode = NULL;
	do{

		printf("\nmenu:\n");
		printf("1] Add new Node ? : \n");
		printf("2] Display Nodes ? : \n");
		printf("3] Search Element ? :\n");
		printf("4] Exit :\n");

		printf("Enter a option --> ");
		scanf("%d",&choice);

		switch(choice){

			case 1: printf("\nEnter a data to add in Node :");
				scanf("%d",&data);
				addNewNode(&headNode,data);
				break;
			case 2:	displayNodes(headNode);
				break;
			case 3: printf("\nEnter a element to search ? ");
				scanf("%d",&data);
				retValue = searchSecondLastOcc(headNode, data);
				if (retValue == -1) { 
					printf(CYN"\t\tNo such element found ..."RESET);
				}else
					printf(CYN"\t\tElem present @ %d th position"RESET,retValue);
				break;
			case 4:	freeAllNodes(&headNode);
				exit(EXIT_SUCCESS);
				break;
			default:
				printf(CYN"\t\tTry again ..."RESET);
		}
	}while(1);
} 
