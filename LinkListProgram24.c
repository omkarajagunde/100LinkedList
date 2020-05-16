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

// This function will check whether the destination list is sublist of source list ...
int subList(SLLNode **srcList, SLLNode **destList){

	if (*srcList == NULL) return -1;
	if (*destList == NULL) return -2;

    int flag = 0;
    int position = 1;
    int count = 0;
    int countDestListNodes = countNodes(&(*destList));
    SLLNode *srcListCpy = *srcList;
    SLLNode *destListCpy = *destList;
    SLLNode *destListTraverseNode = *destList;
    SLLNode *srcListTraverseNode = *srcList;
    int *arr = (int*)calloc(8, sizeof(int));
    int *arrCpy = arr;

	while (srcListCpy != NULL){
        srcListTraverseNode = srcListCpy;
        destListTraverseNode = destListCpy;

        while(destListTraverseNode != NULL && srcListTraverseNode != NULL){

            if (destListTraverseNode -> data == srcListTraverseNode -> data)
                flag += 1;
            else
                flag = 0;    

            srcListTraverseNode = srcListTraverseNode -> nextNode;
            destListTraverseNode = destListTraverseNode -> nextNode;
        }

        if (flag == countDestListNodes)
            *(arrCpy++) = position;

        position += 1;
        srcListCpy = srcListCpy -> nextNode;
        flag = 0;
    }    
	
    arrCpy = arr;
	while(*(arrCpy++) != 0)
        count ++;

    return *(arr + (count - 1));    

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

	int choice, data, viewListChoice, retValue;
	SLLNode *headNodeListOne = NULL, *headNodeListTwo = NULL;
	do{

		printf("\nmenu:\n");
		printf("1] Add new Node (List 1)? : \n");
		printf("2] Add new Node (List 2)? : \n");
		printf("3] Display Nodes ? : \n");
		printf("4] Find last sublist ? :\n");
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
			case 4: 
					retValue = subList(&headNodeListTwo,&headNodeListOne); 
                    if (retValue > 0){
                        printf(CYN"\t\tSub list found @ %d position ..."RESET,retValue);
                    }else{
                        printf(CYN"\t\tNo sublist Found ..."RESET);
                    }
				break;
			case 5: freeAllNodes(&headNodeListTwo);
				exit(EXIT_SUCCESS);
				break;
			default:
				printf(CYN"\t\tTry again ..."RESET);
		}
	}while(1);
} 
