/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
    printf("id = 2017038059\t\tname = Bae Gun Young\n");
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	return 1;
}



void inorderTraversal(Node* ptr)
{
    if(ptr){   //중위순회(왼쪽자식 -> 부모 -> 오른쪽자식)
        inorderTraversal(ptr->left);
        printf("[%d] ", ptr->key);
        inorderTraversal(ptr->right);
    }
}

void preorderTraversal(Node* ptr)
{
    if(ptr){   //전위순회(부모 -> 왼쪽자식 -> 오른쪽자식)
        printf("[%d] ", ptr->key);
        preorderTraversal(ptr->left);
        preorderTraversal(ptr->right);
    }
}

void postorderTraversal(Node* ptr)
{
    if(ptr){   //후위순회(왼쪽자식 -> 오른쪽자식 -> 부모)
        postorderTraversal(ptr->left);
        postorderTraversal(ptr->right);
        printf("[%d] ", ptr->key);
    }
}


int insert(Node* head, int key)
{
    if(head == NULL){  //초기화 안되어있으면 오류메세지 출력
        printf("Not initialized!!!\n");
        return 0;
    }
    Node* temp = head->left;                  //노드포인터
    Node* node = (Node*)malloc(sizeof(node)); //추가할 노드 메모리할당
    node->left = NULL;  //양쪽 링크 NULL
    node->right = NULL;
    node->key = key;    //key값 부여
    if(head->left == NULL){  //첫 노드인경우 head의 왼쪽에 추가하고 함수 종료
        head->left = node;
        return 0;
    }
    else{
        while(1){
            if(key < temp->key){     //key값이 temp의 key값보다 작은 경우
                if(temp->left == NULL){ //temp의 왼쪽이 비어있으면 그쪽에 연결하고 반복문 탈출
                    temp->left = node;
                    break;
                }
                else                    //temp의 왼쪽이 NULL이 아니면 temp 이동
                    temp = temp->left;
            }
            else if(key == temp->key){  //같은 값 존재시 트리에 추가하지않고 반복문 탈출
                free(node);
                break;
            }
            else{                     //key값이 temp의 key값보다 큰 경우
                if(temp->right == NULL){ //temp의 오른쪽이 비어있으면 그쪽에 연결하고 반복문 탈출
                    temp->right = node;
                    break;
                }
                else{                    //temp의 오른쪽이 비어있지 않으면 temp만 이동
                    temp = temp->right;
                }
            }
        }
        return 0;
    }
}

int deleteLeafNode(Node* head, int key)
{
    if(head == NULL){  //초기화 안되어있으면 오류메세지 출력
        printf("Not initialized!!!\n");
        return 0;
    }
    if(head->left == NULL){   //트리에 노드가 없으면 오류메세지 출력
        printf("No nodes!!\n");
        return 0;
    }
    Node* temp = head;     //노드포인터
    Node* del = head->left;//삭제할 노드포인터
    if(del->left == NULL && del->right == NULL){ //트리에 노드수가 하나뿐인 경우
        if(key == del->key){    //key값도 일치시 초기화된 상태로 만듦
            initializeBST(&head);
            return 0;
        }
    }
    while(del != NULL){
        if(key == del->key){    //삭제할 key값을 찾은 경우
            if(del->left == NULL && del->right == NULL){ //리프노드 일 때
                if(del == temp->left){ //del이 temp의 왼쪽이면
                    temp->left = NULL; //temp의 왼쪽 연결해제
                    free(del);
                    break;  //반복문탈출
                }
                else{                   //del이 temp의 오른쪽이면
                    temp->right = NULL; //temp의 오른쪽 연결해제
                    free(del);
                    break;  //반복문 탈출
                }
            }
            else{   //찾은 값의 노드가 리프노드가 아니면 오류메세지 출력후 반복문 탈출
                printf("[%d] is not leaf node!!!\n", key);
                break;
            }
        }
        else{  //key값을 못찾은 경우 temp와 del의 위치 이동
            if(key < del->key){
                temp = del;
                del = del->left;
            }
            else{
                temp = del;
                del = del->right;
            }
        }
    }
    return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
    if(ptr == NULL || key == ptr->key) //ptr이 NULL이겨나 key값을 찾으면 반환하고 함수종료
        return ptr;
    else{                              //key값을 못찾았거나 탐색이 끝나지 않은 경우 계속 탐색 실시
        if(key < ptr->key)
            return searchRecursive(ptr->left, key);
        else
            return searchRecursive(ptr->right, key);
    }
    
}

Node* searchIterative(Node* head, int key)
{
    Node* temp = head->left; //노드포인터
    while(temp != NULL){     //temp가 NULL이 될 때까지 탐색
        if(key == temp->key) //key값을 찾은경우 반환후 종료
            return temp;
        else if(key < temp->key) //key값을 못찾은 경우 temp위치 이동후 계속탐색
            temp = temp->left;
        else
            temp = temp->right;
    }
    return NULL; //temp가 NULL이되어 반복문 탈출시 NULL값 리턴
}


int freeBST(Node* head)
{
    Node* temp = head;      //노드포인터
    Node* del = head->left; //메모리해제할 노드포인터
    if(del == NULL){  //노드미존재시 헤드노드 메모리해제하고 함수종료
        free(temp);
        return 0;
    }
    while(del->left != NULL || del->right != NULL){ //del이 리프노드를 가리킬 때 까지 탐색
        if(del->left != NULL){
            temp = del;
            del = del->left;
        }
        else{
            temp = del;
            del = del->right;
        }
    }
    if(temp->left == del){ //del이 temp의 왼쪽
        free(del);         //del위치 노드 메모리해제
        temp->left = NULL; //temp의 왼쪽 링크해제
        return freeBST(head);  //함수 재실행
    }
    else{                  //del이 temp의 오른쪽
        free(del);         //del위치 노드 메모리해제
        temp->right = NULL;//temp의 오른쪽 링크해제
        return freeBST(head);  //함수 재실행
    }
}
