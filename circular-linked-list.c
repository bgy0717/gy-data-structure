/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);

int item = 0;


int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
    listNode* front = h->rlink; //delete보다 한 칸 앞장서는 노드 포인터
    listNode* delete = h;       //삭제할 노드 포인터
    while(front != h){         //front가 헤드노드로 돌아올 때 까지
        front = front->rlink;  //front 한 칸 이동
        delete = front->llink; //delete 한 칸 이동
        free(delete);    //노드 삭제
    }
    free(front);  //헤드노드 삭제
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //헤드노드가 NULL이면 오류메세지 출력
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; //p를 첫 노드에 위치

	while(p != NULL && p != h) { //모든 노드의 key값 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; 
		i++;
	}
	printf("  items = %d\n", i); //노드 수


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) { //모든 노드와 링크들의 주소 출력
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode)); //추가할 노드에 메모리 할당
    node->key = key;        //key값 부여
    node->rlink = h;        //rlink에 헤드노드 연결
    node->llink = h->llink; //llink에 원래 마지막이었던 노드 연결
    h->llink->rlink = node; //원래 마지막이었던 노드의 rlink에 새 노드 연결
    h->llink = node;        //헤드노드의 llink에 새 노드 연결
	item++;          //노드수 증가
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
    listNode* temp = h->llink; //삭제할 노드 포인터
    h->llink = temp->llink;    //헤드노드의 llink에 끝에서 두 번째 노드 연결
    temp->llink->rlink = h;    //끝에서 두 번째 노드의 rlink에 헤드노드 연결
    free(temp);           //삭제할 노드 메모리 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode)); //추가할 노드에 메모리 할당
    node->key = key;        //key값 부여
    node->rlink = h->rlink; //rlink에 원래 첫번째였던 노드 연결
    node->llink = h;        //llink에 헤드노드 연결
    h->rlink->llink = node; //원래 첫 노드의 왼쪽에 새 노드 연결
    h->rlink = node;        //첫 노드로 지정
	item++;          //노드수 증가

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
    listNode* temp = h->rlink; //삭제할 노드 포인터
    h->rlink = temp->rlink;    //헤드노드의 rlink에 두 번째 노드 연결
    temp->rlink->llink = h;    //두 번째 노드의 llink에 헤드노드 연결
    free(temp);                //삭제할 노드 메모리해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
    if(h->rlink == h)         //노드 없으면 오류메세지 출력
        printf("No nodes\n");
    else{
        listNode* front = h->rlink;    //temp의 선행노드 포인터
        listNode* temp = front->llink; //링크를 바꿀 노드 포인터
        h->llink = h->rlink;          //헤드노드의 llink를 첫 노드에 연결
        while(front != h){            //front와 temp의 위치를 옮겨가며 노드들 역순배치
            temp = front;
            front = front->rlink;
			temp->rlink = temp->llink;
            temp->llink = front;
        }
        h->rlink = temp;  //헤드노드의 rlink를 원래 끝에있던 노드로 연결
    }

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
    if(h->rlink == h){       //헤드노드 제외하고 노드가 없으면 insertFirst 함수 실행하고 함수 종료
        insertFirst(h, key);
        return 0;
    }
    listNode* node = (listNode*)malloc(sizeof(listNode)); //추가할 노드
    listNode* temp = h->rlink;  //노드포인터
    node->key = key;
    while(temp != h){         //temp가 헤드노드로 돌아올 때 까지 탐색
        if(key < temp->key){  //더 큰 key값 찾은경우 그 노드의 앞에 삽입
            node->rlink = temp;
            node->llink = temp->llink;
            temp->llink->rlink = node;
            temp->llink = node;
            break;
        }
        else       //넣을 key값보다 작으면 temp의 위치만 이동
            temp = temp->rlink;
    }
    if(temp == h) //temp가 헤드노드 위치까지 이동했다면 insertLast 실행
        insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
    listNode* temp = h->rlink;   //삭제할 노드 포인터
    while(temp != h){            //temp가 헤드노드로 돌아올 때 까지 탐색
        if(key == temp->key){    //key값을 찾은경우 temp 양옆 노드를 서로 연결하고 temp에 있는 노드 메모리 해제
            temp->llink->rlink = temp->rlink;
            temp->rlink->llink = temp->llink;
            free(temp);
            break;
        }
        else   //key값이 다른 경우 temp의 위치만 이동
            temp = temp->rlink;
    }
	return 0;
}
