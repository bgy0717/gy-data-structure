/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

int item = 0;  //노드수 계산용 전역변수

/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	printf("ID : 2017038059\t\tName : Bae Gun Young\n");
	char command;            //수행할 명령을 입력받을 변수
	int key;                 //노드 추가, 삭제시 입력받을 변수
	headNode* headnode=NULL; //headnode 생성

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {     //입력한 커맨드에 따라 명령수행 or 프로그램 종료
		case 'z': case 'Z':
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //추가될 노트 생성, 공간할당

	node->key = key;         //key값 저장
	node->link = h->first;   //이미 존재하는 노드가 있다면 추가된 노드가 원래 first였던 노드를 link
	h->first = node;         //추가된 노드의 위치를 first로 설정
	item++;       //노드수 증가

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //노드생성
	node->key = key;            //key값 저장
	node->link = NULL;          //link 비우기
	listNode* pre = h->first;   //첫 노드 가리킴
	listNode* mid = pre->link;  //pre의 다음노드
	int count = 1;              //계산횟수 셀 변수
	if(key < pre->key){         //삽입할 노드의 key값이 첫 노드의 key값보다 낮으면 맨 앞으로 배치
		node->link = h->first;
		h->first = node;
		item++;          //노드수 증가
	}
	else{                      //삽입할 노드의 key값이 첫 노드의 key값보다 큰 경우
		while(count != item){  //계산횟수+1이 노드의 수와 같아질 때까지
			if(key < mid->key){   //mid의 key값이 더 크면 그 앞에 삽입
				node->link = mid;
				pre->link = node;
				item++;           //node수 증가
				count = item;     //while문 탈출하기위해 count수 변경
			}
			else{                 //mid의 key값이 크지 않은경우 pre와 mid 한칸씩 이동하고 계산횟수 +1
				pre = pre->link;
				mid = mid->link;
				count++;
			}
		}
		if(node->link == NULL){  //삽입할 노드의 key값보다 더 큰 key값이 없었던 경우
			pre->link = node;    //맨 마지막에 노드 삽입
			item++;              //노드수 증가
		}
	}
	
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //노드생성
	listNode* temp = h->first; //임시노드
	node->key = key;
	node->link = NULL;
	int count = 1;         //계산횟수 변수
	while(count != item){  //temp의 위치를 마지막 노드까지 이동
		temp = temp->link;
		count++;
	}
	temp->link = node;  //마지막노드의 link에 삽입할 노드 연결
	item++;             //노드수 증가
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* temp = h->first;
	temp = temp->link; //첫 노드가될 위치
	h->first = temp;   //first가 바로 temp를 가리키도록 함
	item--;            //노드수 감소

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* temp_front = h->first; //key값을 비교할 노드 위치
	int num = item;                  //현재 노드의 개수 저장변수
	int count = 1;                   //계산횟수를 셀 변수
	if(temp_front->key == key){      //첫 노드의 key값이 삭제할 값인경우
		h->first = temp_front->link; //first가 두 번째 노드를 가리키도록 함
		item--;                      //노드수 감소
	}
	else{	
		listNode* temp_back = h->first; //temp_front의 한칸 전 노드 위치
		temp_front = temp_front->link;
		while(count < item-1){          //temp_front가 마지막 노드를 가리킬 때 까지 반복
			if(temp_front->key == key){ //삭제할 key값을 찾은 경우
				temp_front = temp_front->link; //temp_front를 한 칸 옮기고 back이 바로 가리키도록 함
				temp_back->link = temp_front;
				item--;         //노드수 감소
				count = item;   //while문 탈출하도록 count 변경
			}
			else           //key값이 다른경우 count만 셈
				count++;
			temp_front = temp_front->link; //값 비교후 temp_front, temp_back의 위치 한 칸 이동
			temp_back = temp_back->link;
		}
		if(count != item && temp_front->key == key){ //찾는 key값이 마지막 노드에 있는 경우
			temp_back->link = NULL; //한 칸 앞의 노드에서 link 해제
			item--;                 //노드수 감소
		}
	}
	if(num == item) //삭제할 key값을 가진 노드가 없으면 오류메세지 출력
		printf("Does not exist number\n");
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if(item == 1)       //노드수가 하나뿐이면 deleteFirst로 작업 수행
		deleteFirst(h);
	else{
		listNode* temp = h->first; //임시노드
		int count = 2;         //계산횟수 변수(마지막 노드의 한칸 앞 노드까지 이동하므로 2에서시작)
		while(count < item){  //temp의 위치를 마지막 노드까지 이동
			temp = temp->link;
			count++;
		}
		temp->link = NULL;  //마지막 노드로의 link 해제
		item--;
	}
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* front = h->first; //앞의 노드위치
	listNode* temp = front;     //link를 변경할 노드의위치
	listNode* back = NULL;      //temp의 link대상위치
	front = front->link;
	temp->link = NULL;        //첫 노드 link 해제
	int count = 1;            //계산횟수
	while(count<item){
		back = temp;          //모든 노드의 포인터를 한칸씩 이동시키면서 link 역배치
		temp = front;
		front = front->link;
		temp->link = back;
		count++;
	}
	h->first = temp;  //마지막 노드의 위치를 first가 가리키도록 함
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {       //노드가 없는경우 오류메세지 출력
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {    //first부터 마지막노드까지 차례대로 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i); //총 노드의 수
}

