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
int countNodes(SLLNode **headNode, SLLNode **tailNode){
	
	SLLNode *dummyNode = *headNode;
	int count = 0;
	for (; dummyNode != NULL && dummyNode -> nextNode != (*tailNode) -> nextNode; count++)
		dummyNode = dummyNode -> nextNode;
	return count;
}

// At the time of Termination of program this function is called that will free the memory of heap  ...
void freeAllNodes(SLLNode **headNode, SLLNode **tailNode){
	
	if (*headNode == NULL){return;}
	if ((*headNode)->nextNode == NULL)
		free(*headNode);
	else{
		while ((*headNode)->nextNode != *tailNode){
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
void addNewNode(SLLNode **headNode, SLLNode **tailNode, int num){

	SLLNode *newNode = createNode(num);
	if (*headNode == NULL){
		*headNode = *tailNode = newNode;
        (*tailNode) -> nextNode = *headNode;
		

	}else{
		SLLNode **dummyNode = headNode;
		while((*dummyNode)->nextNode != (*tailNode) -> nextNode){
			dummyNode = &(*dummyNode) -> nextNode;
	
		}
		(*dummyNode)->nextNode = newNode;
        newNode -> nextNode = *headNode;
        *tailNode = newNode;
	}

}

// This function will take a input string and create a linked List from it ..
int createLinkedListFromNumberString(SLLNode **headNode,SLLNode **tailNode, char *string){

    int *tokensFromString = tokeniseString(string, ' ');   // Default delim is single space bar i.e. ' '
    int tokenCount = getTokensCount(string, ' ');           // Default delim is single space bar i.e. ' '

    for (int i = 0; i<tokenCount; i++){
        addNewNode(headNode, tailNode,tokensFromString[i]);
    }

    return 0;


}


// This function makes a copy of Circular linked list ...
int CllCopy(SLLNode **srcList,SLLNode **tailNodeOne, SLLNode **destList, SLLNode **tailNodeTwo){
    
	if (*srcList == NULL) return -1;
	SLLNode *destCpyList = *srcList;
	SLLNode *dummyNode = createNode((*srcList)->data);
	SLLNode *dummyCopy = dummyNode;
	destCpyList = destCpyList -> nextNode;
	do{
        dummyNode -> nextNode = createNode(destCpyList->data);
		dummyNode = dummyNode -> nextNode;
		destCpyList = destCpyList -> nextNode;
    }while(destCpyList != (*tailNodeOne) -> nextNode);

    dummyNode -> nextNode = dummyCopy;
    *tailNodeTwo = dummyNode;
    *destList = dummyCopy;
	return 0;
}

// This function performs inPlace reverse on the Linked List ...
int reverseList(SLLNode **headNode, SLLNode **tailNode){

    SLLNode *nextNode = NULL;
    SLLNode *prevNode = *headNode;
    SLLNode *currentNode = *headNode;
    *tailNode = *headNode;

    do{
        nextNode = currentNode -> nextNode;         // store the nextNode
        currentNode -> nextNode = prevNode;         // reverse the pointer of the nextNode

        prevNode = currentNode;                     // move pointer one step forWard ...
        currentNode = nextNode;
        
    }while(currentNode != *headNode);
    (*headNode) -> nextNode = prevNode;
    *headNode = prevNode;
    return 0;
}


// This function will display the list of all the created nodes ...
void displayNodes(SLLNode **headNode, SLLNode **tailNode){

	SLLNode *dummyNode = *headNode;
    if (dummyNode == NULL){return;}
    do{
        printf("|\033[1;35m %d \033[0| \033[1;36m->\033[0m "RESET,dummyNode->data);
		dummyNode = dummyNode->nextNode;
    }while(dummyNode != *headNode);
}

// This function will whether CLList is palindrome or not...
int listPalindrome(SLLNode **headNodeOne, SLLNode **tailNodeOne){
	SLLNode *reverseListNode = NULL;
    SLLNode *reverseListNodeTailNode = NULL;
    SLLNode *dummyNode = *headNodeOne;

    CllCopy(headNodeOne,tailNodeOne,&reverseListNode,&reverseListNodeTailNode);
    reverseList(&reverseListNode,&reverseListNodeTailNode);
    
    int flag = 0;
    do{
        if (reverseListNode -> data != dummyNode -> data){
            flag = 1;
            break;
        }
        dummyNode = dummyNode -> nextNode;
        reverseListNode = reverseListNode -> nextNode;
    }while(dummyNode != *headNodeOne);

    if (flag == 0)
        return 0;
    else 
        return -1;   
    
}

// Driver code containing a menu to display options ...
void main(void){

	int choice, retValue, data;
    char str[256];
    SLLNode *headNodeOne = NULL;
    SLLNode *tailNodeOne = NULL;
	do{

		printf("\nmenu:\n");
		printf("1] Add new Node (CLList 1)? : \n");
		printf("2] Display Nodes ? : \n");
		printf("3] CHeck CLList 1 Palindrome or not? :\n");
		printf("4] Exit :\n");

		printf("Enter a option --> ");
		scanf("%d",&choice);

		switch(choice){

			case 1: printf("\nEnter nodes data seperated by delimiter(space key i.e ' ') :");
				scanf(" %[^\n]",str);
                printf("\n%s",str);
				createLinkedListFromNumberString(&headNodeOne, &tailNodeOne, str);
				break;     
			case 2:	printf("\nCircular Link List One \n: ");
                displayNodes(&headNodeOne, &tailNodeOne);
				break;
			case 3:
                retValue = listPalindrome(&headNodeOne, &tailNodeOne);
                if (retValue == -1)
                    printf(CYN"\t\tCLList NOT palindrome."RESET);
                if (retValue == 0){
                    printf(CYN"\t\tCLList is palindrome."RESET);
                    printf("\nCircular Link List Two \n: ");
                    displayNodes(&headNodeOne, &tailNodeOne);  
                }
                break;
			case 4: freeAllNodes(&headNodeOne, &tailNodeOne);
				exit(EXIT_SUCCESS);
				break;
			default:
				printf(CYN"\t\tTry again ..."RESET);
		}
	}while(1);
} 
