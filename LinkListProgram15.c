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

// Function that creates a indivisual node and assigns feilds of the node
SLLNode *createNode(int num){
	
	SLLNode *newNode = (SLLNode*)malloc(sizeof(SLLNode));
	newNode->nextNode = NULL;
	newNode->data = num;
	return newNode;
}

// This function will count the nodes in the List
int countNodes(SLLNode **headNode){
	
	SLLNode *dummyNode = *headNode;
	int count = 0;
	for (; dummyNode != NULL; count++)
		dummyNode = dummyNode -> nextNode;
	printf("\t\t\nodes total = %d",count);
	return count;
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

}

// This function will concat the 2nd Link list's start-end range nodes to the 1st Link List ..
int concatListRange(SLLNode **sourceList, SLLNode **destList,int start, int end){

	SLLNode *sourceListCopy = *sourceList;
	SLLNode *destStart = *destList;
	SLLNode *destEnd = *destList;
	int i = 1;

	while (sourceListCopy -> nextNode != NULL)
		sourceListCopy = sourceListCopy -> nextNode;
	
	while (i != start){
		
		destStart = destStart -> nextNode;
		i++;
	}

	i = 1;
	while (i != end){
		
		destEnd = destEnd -> nextNode;
		i++;
	}

	free(destEnd->nextNode);
	destEnd->nextNode = NULL;
	sourceListCopy -> nextNode = destStart;

	return 0;


	return 0;

}

// This function will display the list of all the created nodes ...
void displayNodes(SLLNode **headNode){

	SLLNode *dummyNode = *headNode;
	while(dummyNode != NULL){
		printf("|\033[1;35mdata: %d \033[0| \033[1;36m->\033[0m "RESET,dummyNode->data);
		dummyNode = dummyNode->nextNode;
	}
}


// Driver code containing a menu to display options ...
void main(void){

	int choice, attempt = 1, data, viewListChoice, start, end;
	SLLNode *headNodeListOne = NULL, *headNodeListTwo = NULL;
	do{

		printf("\nmenu:\n");
		printf("1] Add new Node (List 1)? : \n");
		printf("2] Add new Node (List 2)? : \n");
		printf("3] Display Nodes ? : \n");
		printf("4] Concat n no.of element from List 1 @ end of List 2 ? :\n");
		printf("5] Exit :\n");

		printf("Enter a option --> ");
		scanf("%d",&choice);

		switch(choice){

			case 1: printf("\nEnter a data to add in Node :");
				scanf("%d",&data);
				addNewNode(&headNodeListOne,data);
				break;
			case 2: printf("\nEnter a data to add in Node :");
				scanf("%d",&data);
				addNewNode(&headNodeListTwo,data);
				break;
			case 3:	printf("\n\tView list 1 or 2 [1/2] :");
				scanf("%d",&viewListChoice);
				if (viewListChoice == 1)
					displayNodes(&headNodeListOne);
				else
					displayNodes(&headNodeListTwo);
				break;
			case 4: if(attempt == 1){
					printf("Enter start element to copy from list 1? :");
					scanf("%d",&start);
					printf("Enter end element to copy from list 1? :");
					scanf("%d",&end);
					concatListRange(&headNodeListTwo,&headNodeListOne,start,end); 
				attempt += 1;
				}else
					printf(CYN"\t\tCant concat 2nd time otherwise it will become Circular Linked List ..."RESET);
				break;
			case 5: freeAllNodes(&headNodeListTwo);
				exit(EXIT_SUCCESS);
				break;
			default:
				printf(CYN"\t\tTry again ..."RESET);
		}
	}while(1);
} 
