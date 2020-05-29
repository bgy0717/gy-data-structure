/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	for(int i=0; i<MAX_STACK_SIZE; i++) //스택 초기화
		stack[i] = NULL;
		top = -1;
	while(1){
		while(node != NULL){ //현재 노드위치에서 왼쪽 끝까지 push하면서 이동
		push(node);
		node = node->left;
		}
	node = pop();      //노드하나 pop
	if(node == NULL)   //가져온 노드가 없으면 반복문 탈출
		break;
	printf(" [%d] ", node->key); //가져온 노드의 값 출력
	node = node->right;          //가져온 노드의 오른쪽으로 이동하여 반복문 계속
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if(ptr == NULL){           //노드가 없으면 메세지 출력후 함수 종료
		printf("No Nodes!!!\n");
		return;
	}
	front = -1;                 //Queue 초기화
	rear = -1;
	for(int i = 0; i<MAX_QUEUE_SIZE; i++)
		queue[i] = NULL;
	enQueue(ptr);              //root 노드 큐에 추가
	while(1){
		ptr = deQueue();       //Queue의 노드 하나 가져옴
		if(ptr == NULL)        //가져온 노드가 없으면 종료
			break;
		printf(" [%d] ", ptr->key); //key값 출력
		if(ptr->left)               //가져온 노드의 왼쪽에 노드가 있으면 큐에 추가
			enQueue(ptr->left);
		if(ptr->right)              //오른쪽에도 노드가 있으면 큐에 추가
			enQueue(ptr->right);
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* temp = head;            //del을 따라갈 노드포인터
	Node* del = head->left;       //삭제할 노드포인터
	while(del){
		if(key == del->key)       //key값을 찾으면 탈출
			break;
		else if(key < del->key){  //찾을값이 작으면 왼쪽으로 이동
			temp = del;
			del = del->left;
		}
		else{                     //찾을값이 더 크면 오른쪽으로 이동
			temp = del;
			del = del->right;
		}
	}
	if(del == NULL){               //찾는값이 없으면 오류메세지 출력후 함수종료
		printf("No number!!!!\n");
		return 0;
	}
	else if(del->left == NULL && del->right == NULL){ //삭제할 노드가 리프노드
		if(temp->left == del){  //del의 위치에 따라 이전 노드로부터 연결해제 후 메모리 반환
			temp->left = NULL;
			free(del);
		}
		else{
			temp->right = NULL;
			free(del);
		}
	}
	else {                        //삭제할 노드가 리프노드가 아닌경우
		Node* mod = del;          //원래 삭제할 노드(key값 변경하여 제거)
		if(del->left){            //삭제할 노드의 왼쪽노드가 존재하면 왼쪽 서브트리의 맨 오른쪽 노드로 del 이동
			temp = del;
			del = del->left;
			while(del->right){
				temp = del;
				del = del->right;
			}
			mod->key = del->key;    //이동한 노드의 key값으로 삭제하려던 노드의 key값을 변경
			if(temp->right == del){ //del노드의 위치에 따라 삭제
				if(del->left){         //제거할 노드의 왼쪽에 노드존재시 윗노드의 오른쪽에 연결
					temp->right = del->left;
					free(del);
				}
				else{                  //미존재시 윗노드의 오른쪽 링크 NULL
					temp->right = NULL;
					free(del);
				}
			}
			else{                   //del노드의 위치에 따라 삭제(위의 반대경우)
				if(del->right){
					temp->left = del->right;
					free(del);
				}
				else{
					temp->left = NULL;
					free(del);
				}
			}
		}
		else{                   //삭제할 노드의 왼쪽노드 미존재시 위의 반대로 진행
			temp = del;
			del = del->right;
			while(del->left){
				temp = del;
				del = del->left;
			}
			mod->key = del->key;
			if(temp->left == del){
				temp->left = NULL;
				free(del);
			}
			else{
				temp->right = NULL;
				free(del);
			}
		}
	}
	return 0;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	return stack[top--];     //top의 원소 리턴하고 top 위치변경
}

void push(Node* aNode)
{
	if(top+1 == MAX_STACK_SIZE)   //스택이 꽉 찬 상태면 오류메세지
		printf("Stack Full!!!\n");
	else
		stack[++top] = aNode;    //스택에 원소 추가
}



Node* deQueue()
{
	return queue[(++front)%MAX_QUEUE_SIZE]; //front증가시키고 원소 리턴
}

void enQueue(Node* aNode)
{
	int r = (++rear)%MAX_QUEUE_SIZE;
	if(front == (rear+1)%MAX_QUEUE_SIZE)  //큐가 꽉 찬 상태면 오류메세지 출력
		printf("Queue Full!!!\n");
	else
		queue[r] = aNode; //큐에 원소 추가
}


void printStack(){
	printf("[Stack]\n");
	int i = 0;
	while(stack[i]){     //스택의 원소가 없을 때까지 출력
		printf("stack[%d] = %d\n", i, stack[i]->key);
		i++;
	}
	printf("item = %d",i); //원소갯수
}


