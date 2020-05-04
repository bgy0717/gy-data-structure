/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

int item = 0;     //노드수 계산용 전역변수

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);  

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
    printf("ID : 2017038059\t\t Name : Bae Gun Young\n");
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode); 
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {  //초기화함수, 함수를 int 타입으로 선언하고 헤드노드의 주소를 직접받아 조작
    if(*h != NULL)    //할당된 메모리가 있으면 초기화
		freeList(*h);
    *h = (headNode*)malloc(sizeof(headNode)); //헤드노드에 메모리 할당
	(*h)->first = NULL;                       //첫 노드가 없으므로 NULL 가리키도록 함
	item = 0;
	return 1;
}

int freeList(headNode* h){
	listNode* front = h->first; //해제할 노드의 뒷노드
	listNode* node;             //해제할 노드
	while(front != NULL){       //첫 노드부터 순서대로 메모리 해제
		node = front;
		front = front->rlink;
		free(node);
	}
	free(h);    //헤드노드의 메모리 해제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {     //노드가 없는경우 오류메세지 출력 후 리턴
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {     //첫 노드부터 차례대로 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i); //노드수
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	if(item ==0){             //노드가 없으면 insertFirst함수로 실행
		insertFirst(h, key);
		return 0;
	}
	listNode* node = (listNode*)malloc(sizeof(listNode)); //추가할 노드 메모리 할당
	node->key = key;   //key값 부여
	node->rlink = NULL;//마지막 노드로 삽입할 것이므로 rlink에 NULL 연결
	listNode* temp = h->first; //노드 포인터 생성후 마지막 노드로 이동
	for(int i =1; i<item; i++)
		temp = temp->rlink;
	temp->rlink = node; //마지막 노드의 rlink에 노드연결
	node->llink = temp; //마지막이었던 노드에 llink 연결
	item++;  //노드수 증가
	
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if(item ==0){       //노드가 없으면 오류메세지 출력
		printf("No nodes\n");
		return 0;
	}
	if(item ==1){       //노드가 하나면 첫 노드 삭제 함수로 처리
		deleteFirst(h);
		return 0;
	}
	listNode* temp = h->first;  //마지막 노드의 위치를 가리킬 포인터
	for(int i = 1; i<item; i++) //temp를 마지막 노드위치까지 이동
		temp = temp->rlink;
	temp->llink->rlink = NULL; //삭제할 앞 노드의 rlink 해제
	free(temp);
	item--;     //노드수 감소

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode)); //추가할 노드에 메모리 할당
    node->key = key;        //key값 부여
    node->rlink = h->first; //rlink가 첫 노드를 가리키도록 함
    node->llink = NULL;     //llink는 비워둠
    h->first = node;        //첫 노드로 지정
	item++;          //노드수 증가
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if(item ==0){         //노드가 없으면 오류메세지 출력
		printf("No nodes\n");
		return 0;
	}
	listNode* temp = h->first; //첫 노드를 가리킴
	if(item ==1){        //노드가 하나뿐이면 first를 NULL 가리키고 temp 메모리 해제
		h->first = NULL;
		free(temp);
	}
	else{                //노드가 여러개인 경우
		h->first = temp->rlink;    //두 번째 노드를 첫 노드로 설정
		temp->rlink->llink = NULL; //두 번째 노드의 llink 해제
		free(temp); //삭제할 노드의 메모리 해제
		item--;     //노드수 감소
	}
	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	if(item <2)                 //노드 수가 2개보다 적으면 그대로 반환
		return 0;
	listNode* front = h->first->rlink; //노드 포인터변수
	listNode* back = h->first;         //front의 한 칸 앞의 포인터변수
	for(int i = 2; i<item; i++){    //front가 마지막 노드를 가리키도록 이동
		front = front->rlink;
		back = back->rlink;
	}
	h->first = front;           //마지막 노드를 first로 지정
	front->llink = NULL;        //마지막 두 노드의 invert
	front->rlink = back;
	back->rlink = back->llink;
	back->llink = front;
	front = front->rlink;
	back = back->rlink;
	if(item > 2){              //노드 수가 2개보다 많으면 추가 연산 실행    
		for(int i = 3; i<item; i++){     //가운데의 노드들 invert
			back->rlink = back->llink;
			back->llink = front;
			front = front->rlink;
			back = back->rlink;
		}
		back->llink = front;   //원래 맨 앞이었던 노드 invert
		back->rlink = NULL;
	}
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	if(item ==0){              //노드가 없으면 insertFirst 함수로 실행
		insertFirst(h, key);
		return 0;
	}
	listNode* node = (listNode*)malloc(sizeof(listNode)); //추가할 노드에 메모리 할당
	node->key = key;     //key값을 넣고 link 초기화
	node->llink = NULL;
	node->rlink = NULL;
	listNode* temp = h->first; //key값 비교할 포인터 변수
	if(key < temp->key){    //첫 노드보다 key값이 작은경우
		node->rlink = temp; //rlink에 첫 노드 연결
		temp->llink = node; //첫 노드의 llink에 노드 연결
    	h->first = node;    //첫 노드로 가리키도록 함
		item++;         //노드수 증가
	}
	else{
		for(int i = 1; i<item; i++){ //temp 이동해가며 key값 비교
			temp = temp->rlink;
			if(key < temp->key){    //더 큰 key값 가진 노드 발견시 temp와 그 앞 노드 사이에 노드 삽입
				node->rlink = temp;
				node->llink = temp->llink;
				temp->llink->rlink = node;
				temp->llink = node;
				item++;      //노드수 증가
				i = item;    //반복문 탈출하도록 i값 변경
			}
		}
	}
	if(node->rlink == NULL){ //더 큰 key값을 가진 노드 미발견시
		temp->rlink = node;  //마지막 노드의 rlink에 node 연결
		node->llink = temp;  //노드의 llink에 마지막 이었던 노드 연결
		item++;   //노드수 증가
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* temp = h->first; //key값 비교할 포인터
	if(temp->key == key)       //첫 노드의 key값이 삭제할 값인경우
		deleteFirst(h);        //첫 노드 삭제 함수 실행
	else{                              //찾는 값이 첫 노드의 값이 아닌 경우
		for(int i = 1; i<item; i++){   //노드의 수만큼 key값 탐색
			if(temp->key == key){      //key값을 찾은 경우 temp의 위치를 그대로 두고 반복문 탈출
				i = item;
			}
			else                       //찾는 값이 아닌경우
				temp = temp->rlink;    //temp의 위치 이동
		}
		if(temp->rlink != NULL){              //temp의 위치가 끝이 아닌 데서 멈춘경우
			temp->llink->rlink = temp->rlink; //temp의 양쪽 노드를 서로 link
			temp->rlink->llink = temp->llink;
			free(temp);                       //temp위치의 노드 메모리 해제
			item--;                           //노드수 감소
		}
		else{                        //temp가 끝까지 이동한 경우
			if(temp->key == key)     //key값 일치시 마지막 노드 삭제 함수 실행
				deleteLast(h);
			else                     //찾는 key값이 없던 경우 오류메세지 출력
				printf("Does not exist number\n\n");
		}
	}
	return 1;
}
