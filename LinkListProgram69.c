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
    struct node *prevNode;
}SLLNode;

// Function that creates a indivisual node and assigns feilds of the node
SLLNode *createNode(int num){
	
	SLLNode *newNode = (SLLNode*)malloc(sizeof(SLLNode));
	newNode->nextNode = NULL;
    newNode->prevNode = NULL;
	newNode->data = num;
	return newNode;
}

// This function will count the nodes in the List
int countNodes(SLLNode **headNode){
	
	SLLNode *dummyNode = *headNode;
	int count = 0;
	for (; dummyNode != NULL; count++)
		dummyNode = dummyNode -> nextNode;
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
        newNode -> prevNode = *dummyNode;
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

// This function will remove the specified element of the DLList ...
int searchLastOcc(SLLNode *headNode, int searchElem){
    
    int posTracker = 1;
	int lastOcc = 0;
	SLLNode *dummyNode = headNode;
	while (dummyNode != NULL){

		if (dummyNode -> data == searchElem )
			lastOcc = posTracker;
			
		posTracker += 1;
		dummyNode = dummyNode -> nextNode;
	}
	if (lastOcc > 0 && lastOcc <= countNodes(&headNode))
		return lastOcc;
	else
		return -1;

}

// This function will display the list of all the created nodes ...
void displayNodes(SLLNode **headNode){

	SLLNode *dummyNode = *headNode;
	while(dummyNode != NULL){
		printf("|\033[1;35m %d \033[0| \033[1;36m<=>\033[0m "RESET,dummyNode->data);
		dummyNode = dummyNode->nextNode;
	}
}


// Driver code containing a menu to display options ...
void main(void){

	int choice, data, viewListChoice, retValue, pos;
    char str[256];
	SLLNode *headNodeListOne = NULL;
	do{

		printf("\nmenu:\n");
		printf("1] Add new Node (DLList 1)? : \n");
		printf("2] Display Nodes ? : \n");
		printf("3] Search last occurence in DLList 1 ? :\n");
		printf("4] Exit :\n");

		printf("Enter a option --> ");
		scanf("%d",&choice);

		switch(choice){

			case 1: printf("\nEnter nodes data seperated by delimiter(space key i.e ' ') :");
				scanf(" %[^\n]",str);
                printf("\n%s",str);
				createLinkedListFromNumberString(&headNodeListOne, str);
				break;
			case 2:	displayNodes(&headNodeListOne);
				break;
			case 3: 
                printf("Enter data to search :");
                scanf("%d",&pos);
                retValue = searchLastOcc(headNodeListOne, pos);
                if (retValue == -1)    
                    printf(CYN"\t\tNo nodes present of such data ..."RESET);
                else
                    printf(CYN"\t\tlast occurence found @ %d ..."RESET, retValue);
				break;
			case 4: freeAllNodes(&headNodeListOne);
				exit(EXIT_SUCCESS);
				break;
			default:
				printf(CYN"\t\tTry again ..."RESET);
		}
	}while(1);
} 
