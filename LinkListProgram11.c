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

// This function will search a particular element's
// occurence and return its no. of occurences ...
int searchAll(SLLNode *headNode, int searchElem){
	
	int countOcc = 0;
	SLLNode *countNodeOcc = headNode;

	for (int i = 0; countNodeOcc != NULL; i++){
		if (countNodeOcc -> data == searchElem)
			countOcc ++;
		countNodeOcc = countNodeOcc -> nextNode;
	}
	
	free(countNodeOcc);
	return countOcc;
}

// This function will display the list of all the created nodes ...
void displayNodes(SLLNode *headNode){

	SLLNode *dummyNode = headNode;
	while(dummyNode != NULL){
		printf("|\033[1;35mdata: %d \033[0| \033[1;36m->\033[0m "RESET,dummyNode->data);
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
		printf("3] Display total ocuurences ? :\n");
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
				retValue = searchAll(headNode, data);
				printf(CYN"Total %d occurence found for %d .."RESET, retValue, data);	
				break;
			case 4:	freeAllNodes(&headNode);
				exit(EXIT_SUCCESS);
				break;
			default:
				printf(CYN"\t\tTry again ..."RESET);
		}
	}while(1);
} 
