/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //크기4인 큐 생성
	int front, rear;               //front와 rear의 위치 변수
}QueueType;


QueueType *createQueue();
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);

element getElement();


int main(void)
{
	printf("id : 2017038059\t\t name : Bae Gun Young\n");
	QueueType *cQ = createQueue(); //큐 생성하여 포인터변수 cQ에 저장
	element data;

	char command;                  //수행할 명령을 받을 변수

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //명령입력

		switch(command) {        //명령에 따라 작업 수행
		case 'i': case 'I':      //Insert 선택시
			data = getElement(); //넣을 값 입력
			enQueue(cQ, data);   //데이터 추가 함수 실행
			break;
		case 'd': case 'D':      //Delete 선택
			deQueue(cQ,&data);   //데이터 삭제 함수 실행
			break;
		case 'p': case 'P':      //PrintQ 선택
			printQ(cQ);          //Queue출력 함수 실행
			break;
		case 'b': case 'B':      //Dubug 선택
			debugQ(cQ);          //디버그 함수 실행
			break;
		case 'q': case 'Q':      //Quit 선택
			break;
		default:                 //선택지 이외의 문자 입력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//에러메세지 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); //위의 과정을 Quit 선택 전까지 반복


	return 1;
}


QueueType *createQueue()  //Queue생성
{
	QueueType *cQ;        //구조체 포인터 CQ 생성
	cQ = (QueueType *)malloc(sizeof(QueueType)); //cQ에 메모리할당
	cQ->front = 0;      //front 초기위치
	cQ->rear = 0;       //rear 초기위치
	for(int i = 0; i<MAX_QUEUE_SIZE; i++) //cQ->queue 모든원소를 공백으로 초기화(그냥실행시 이상한값 떠서 추가)
		cQ->queue[i] = '\0';
	return cQ;
}

element getElement()  //입력할 데이터
{
	element item;     //데이터를 받을 변수
	printf("Input element = ");
	scanf(" %c", &item);  //데이터 입력
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)    //텅 빈 Queue인지 확인할 함수
{
	if(cQ->front == cQ->rear) //front와 rear의 값이 같으면(초기상태)
		return 1;             //1반환 (비어있는 것이 맞음)
	else
		return 0;             //아닌경우 0반환 (비어있지않음)
}

/* complete the function */
int isFull(QueueType *cQ)    //꽉 찬 Queue인지 확인할 함수
{
	if(cQ->front == (cQ->rear+1)%4) //front가 rear의 한 칸 위에 위치시(Queue에 3개의 원소가 들어있는 경우)
		return 1;   //1반환(꽉 찬 상태가 맞음)
	else
		return 0;   //아닌경우 0반환(꽉 찬 상태가 아님)
}


/* complete the function */
void enQueue(QueueType *cQ, element item) //Queue에 데이터 추가 함수
{
	if(isFull(cQ)==1)                     //Queue가 꽉 찬 경우
		printf("Queue is Full!!!!\n");    //오류메세지 출력
	else{                                          //꽉 찬 상태가 아닌 경우
		cQ->rear =(cQ->rear + 1) % MAX_QUEUE_SIZE; //rear위치 변경
		cQ->queue[cQ->rear] = item;                //바뀐 rear의 위치에 값 입력
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item) //Queue 데이터 삭제 함수
{
    if(isEmpty(cQ)==1)                  //Queue가 텅 빈 경우
		printf("Queue is Empty!!!!\n"); //오류메세지 출력
	else{                                            //텅 비어있지 않은 경우
		cQ->front =(cQ->front + 1) % MAX_QUEUE_SIZE; //front위치 변경
		cQ->queue[cQ->front] = '\0';                 //front위치의 값 제거
	}
}


void printQ(QueueType *cQ) //Queue 출력 함수
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;//첫 값(front의 한 칸 위의 값)
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;  //마지막 값()

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]); //첫 값부터 끝 값까지 출력
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) //debug창 표시함수
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)  //queue 사이즈만큼 실행
	{
		if(i == cQ->front) {                 //front위치 찾아서 표시
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //저장된 문자 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front와 rear의 위치 출력
}


