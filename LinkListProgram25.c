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
	printf("\t\tTotal Nodes = %d",count);
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

// This function will count no. of tokens in a string on a delim
int getTokensCount(char *string, char delim){

    int tokenCounter = 0;
    char *strCpy = string;
    int flag = 0;
    char ch;

    while((ch = *(strCpy++)) != '\0'){
        
        if(ch == delim && flag){
            
            tokenCounter += 1;
            flag = 0;
        }
        if(ch != delim){
            flag = 1;
        }
        if(ch == delim && *strCpy == '\0')
            tokenCounter -= 1;
        
    }
    
    return tokenCounter + 1;

}

// This function will tokenise a string on a specific delimiter and return 
// the pointer to int array converted of the string 
int *tokeniseString(char *string, char delim){

    int tokenCounter = 0;
    int *tokenArray;
    int *iTokenArr;
    int num;
    char *strCpy = string;
    char buffer[10];
    int iBuff = 0;
    int flag = 0;
    char ch;
    
    tokenCounter = getTokensCount(string, delim);

    tokenArray = (int*) malloc(tokenCounter * sizeof(int));
    iTokenArr = tokenArray;
    strCpy = string;
    flag = 0;
    while((ch = *(strCpy++)) != '\0'){
        
        if(ch == delim && flag){
            
            buffer[iBuff] = '\0';
            *(iTokenArr++) = atoi(buffer);
            iBuff = 0;
            flag = 0;
        }
        if(ch != delim){
            
            *(buffer + iBuff) = ch;
            iBuff ++;
            flag = 1;
        }
        if(*strCpy == '\0'){
            
            buffer[iBuff] = '\0';
            *(iTokenArr++) = atoi(buffer);
        }
        
    }
    return tokenArray;
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

// This function will take a input string and create a linked List from it ..
int createLinkedListFromNumberString(SLLNode **headNode, char *string){

    SLLNode *dummyNode = *headNode;
    int *tokensFromString = tokeniseString(string, ' ');   // Default delim is single space bar i.e. ' '
    int tokenCount = getTokensCount(string, ' ');           // Default delim is single space bar i.e. ' '

    for (int i = 0; i<tokenCount; i++){
        addNewNode(headNode,tokensFromString[i]);
    }

    return 0;


}

void swapFunction(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

// This function take a array sorts it and returns back the array ..
// Bubble sort is used here ... as it is simple and efficeint somewhat ...
void bubbleSort(int *arr, int arrLength){

    for (int i = 0; i<arrLength - 1; i++){
        for (int j = 0; j<arrLength - i - 1; j++){

            if (arr[j] > arr[j+1]){
                swapFunction(&arr[j], &arr[j+1]);
            }
        }
    }

}

// This function will copy the nodes from Src linked list to destination linked list
// in ascending order of their respective data ...
int copyAsc(SLLNode **srcList, SLLNode **destList){

    SLLNode *dummyNode = *srcList;
    int countSrcListNodes = countNodes(&(*srcList));
    int *dataArr = (int*) malloc (countSrcListNodes * sizeof(int));
    int *ptrDataArr = dataArr;
    while (dummyNode != NULL){
        *(ptrDataArr ++ ) = dummyNode -> data;
        dummyNode = dummyNode -> nextNode;
    }

    bubbleSort(dataArr, countSrcListNodes);

    for (int i = 0; i<countSrcListNodes; i++)
        addNewNode(destList, dataArr[i]);

    return 0;

}

// This function will display the list of all the created nodes ...
void displayNodes(SLLNode **headNode){

	SLLNode *dummyNode = *headNode;
	while(dummyNode != NULL){
		printf("|\033[1;35m %d \033[0| \033[1;36m->\033[0m "RESET,dummyNode->data);
		dummyNode = dummyNode->nextNode;
	}
}


// Driver code containing a menu to display options ...
void main(void){

	int choice, data, viewListChoice, retValue;
    char str[256];
	SLLNode *headNodeListOne = NULL, *headNodeListTwo = NULL;
	do{

		printf("\nmenu:\n");
		printf("1] Add new Node (List 1)? : \n");
		printf("2] Display Nodes ? : \n");
		printf("3] Copy list 1 @ list 2 in ascending Order ? :\n");
		printf("4] Exit :\n");

		printf("Enter a option --> ");
		scanf("%d",&choice);

		switch(choice){

			case 1: printf("\nEnter nodes data seperated by delimiter(space key i.e ' ') :");
				scanf(" %[^\n]",str);
                printf("\n%s",str);
				createLinkedListFromNumberString(&headNodeListOne, str);
				break;
			case 2:	printf("\n\tView list 1 or 2 [1/2] :");
				scanf("%d",&viewListChoice);
				if (viewListChoice == 1)
					displayNodes(&headNodeListOne);
				else
					displayNodes(&headNodeListTwo);
				break;
			case 3: headNodeListTwo = NULL;
                copyAsc(&headNodeListOne, &headNodeListTwo);
				break;
			case 4: freeAllNodes(&headNodeListTwo);
				exit(EXIT_SUCCESS);
				break;
			default:
				printf(CYN"\t\tTry again ..."RESET);
		}
	}while(1);
} 
