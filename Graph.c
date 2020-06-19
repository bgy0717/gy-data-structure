
#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX 20

typedef struct Vertex{
    int num;
    struct Vertex* link;
} Vertex;

typedef struct VertexHead {
    Vertex* head;
} VertexHead;

typedef struct Graph {
    VertexHead* vlist;
	
} Graph;


Graph* createGraph(Graph* g);
Graph* destroyGraph(Graph* g);
int insertVertex(Graph* g, int num);
int deleteVertex(Graph* g, int num);
int insertEdge(Graph* g, int num1, int num2);
int deleteEdge(Graph* g, int num1, int num2);
void depthFS(Graph* g, int num);
void breadthFS(Graph* g, int num);
void printGraph(Graph* g);
void freeVertex(Vertex* v); //vertex의 link들 메모리 해제하기위한 함수

int stack[MAX_VERTEX];
int Queue[MAX_VERTEX];
int front = -1;
int rear = -1;
void printQueue();

int main() {
	printf("ID : 2017038059\t\tName : Bae Gun Young");
    char command;
	int num, num2;
	Graph *glist = NULL;
do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                           Graph                                \n");
		printf("----------------------------------------------------------------\n");
		printf(" Create Graph         = c      Destroy Graph                = e \n");
		printf(" Insert Vertex        = i      Delete Vertex                = d \n");
		printf(" Insert Edge          = s      Delete Edge                  = l \n");
		printf(" Depth First Search   = t      Breadth First Search         = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);
		
		switch(command) {
        case 'c': case 'C':
            glist = createGraph(glist);
            break;

        case 'e': case 'E':
			glist = destroyGraph(glist);
            break;

		case 'i': case 'I':
			if(glist == NULL){ //그래프가 없으면 오류메세지 출력
				printf("No graph!!!\n\n");
				break;
			}
			printf("Vertex num : ");
			scanf("%d", &num);		
			insertVertex(glist, num);
			break;

		case 'd': case 'D':
			if(glist == NULL){ //그래프가 없으면 오류메세지 출력
				printf("No graph!!!\n\n");
				break;
			}
			printf("Vertex num : ");
			scanf("%d", &num);
			deleteVertex(glist, num);
			break;

		case 's': case 'S':
			if(glist == NULL){ //그래프가 없으면 오류메세지 출력
				printf("No graph!!!\n\n");
				break;
			}
			printf("Vertex 1 : ");
			scanf("%d", &num);
			printf("Vertex 2 : ");
			scanf("%d", &num2);
			insertEdge(glist, num, num2);
			break;
		
		case 'l': case 'L':
			if(glist == NULL){ //그래프가 없으면 오류메세지 출력
				printf("No graph!!!\n\n");
				break;
			}
			printf("Vertex 1 : ");
			scanf("%d", &num);
			printf("Vertex 2 : ");
			scanf("%d", &num2);
			deleteEdge(glist, num, num2);
			break;

		case 't': case 'T':
			printf("Vertex Num : ");
			scanf("%d", &num);
			for(int i = 0; i<MAX_VERTEX; i++) //스택 초기화
				stack[i] = -1;
			if(glist->vlist[num].head == NULL){
				printf("No Vertex!!!\n");
				break;
			}
			depthFS(glist, num);
			break;

		case 'b': case 'B':
			printf("Vertex Num : ");
			scanf("%d", &num);
			front = -1;  //큐 초기화
			rear = -1;
			breadthFS(glist, num);
			break;

		case 'p': case 'P':
			if(glist == NULL){ //그래프가 없으면 오류메세지 출력
				printf("No graph!!!\n\n");
				break;
			}
			printGraph(glist);
			break;

		case 'q': case 'Q':
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


Graph* createGraph(Graph* g){
	g = (Graph*)malloc(sizeof(Graph));         //그래프 공간할당
	g->vlist = (VertexHead*)malloc(MAX_VERTEX * sizeof(VertexHead)); //리스트에 공간할당
	for(int i = 0; i<MAX_VERTEX; i++){   //모든 리스트의 헤드가 가리키는 주소 초기화
		g->vlist[i].head = NULL;
	}
	return g;
}

Graph* destroyGraph(Graph* g){
	if(g == NULL){ //그래프가 없으면 오류메세지 출력
		printf("No graph!!!\n\n");
		return g;
	}
	for(int i = 0; i<MAX_VERTEX; i++){
		if(g->vlist[i].head != NULL){
			Vertex* v = g->vlist[i].head;
			freeVertex(v);            //Edge 전부 제거
			g->vlist[i].head = NULL;  //Vertex 제거
		}
	}
	free(g);
	g = NULL;
	return g;
}

int insertVertex(Graph* g, int num){
	if(num >= MAX_VERTEX){            //범위밖의 vertex 추가시 오류메세지 출력
		printf("Input Number 0 ~ 19!!\n\n");
		return 0;
	}
	if(g->vlist[num].head != NULL){
		printf("Already Exist Vertex!!!\n\n"); //이미 존재하는 vertex 추가시 오류메세지 출력
		return 0;
	}
	Vertex* vtx = (Vertex*)malloc(sizeof(Vertex)); //Vertex 공간할당
	vtx->link = NULL;
	vtx->num = num;
	g->vlist[num].head = vtx;   //추가한 번호의 리스트의 헤드에 vertex 삽입
	return 0;
	}

int deleteVertex(Graph* g, int num){
	Vertex* v = g->vlist[num].head; //Edge 제거할 포인터
	if(v == NULL){          //없는 Vertex인 경우 오류메세지
		printf("No Vertex!!!\n\n");
		return 0;
	}
	int Enum = -1;
	v = v->link;  //첫 Edge로 연결
	while(v){
		Enum = v->num;
		v = v->link;
		deleteEdge(g, num, Enum);
	}    //삭제할 Vertex의 Edge 모두 제거
	v = g->vlist[num].head;

	//Vertex 제거
	free(v);  
	g->vlist[num].head = NULL; 


	return 0;
}

int insertEdge(Graph* g, int num1, int num2){
	if(g->vlist[num1].head == NULL || g->vlist[num2].head == NULL || num1 >= MAX_VERTEX || num2 >= MAX_VERTEX){
		printf("No Vertex!!!\n\n");  //없는 vertex 번호거나 20이상의 숫자 전달시 오류메세지
		return 0;
	}
	Vertex* p1, *p2;  //num1, num2 번째 vertex 포인터
	p1 = g->vlist[num1].head;
	p2 = g->vlist[num2].head;
	while(p1->link != NULL){ //p1에 연결되어있는 마지막 Vertex 까지 이동
		p1 = p1->link;
		if(p1->num == num2){ //이미 Edge가 존재시 메세지 출력후 중단
			printf("Already exist Edge!!!\n\n");
			return 0;
		}
	}
	while(p2->link != NULL){ //p2 끝까지 이동
		p2 = p2->link;
	}
	Vertex* v1 = (Vertex*)malloc(sizeof(Vertex)); //연결할 vertex 공간할당
	Vertex* v2 = (Vertex*)malloc(sizeof(Vertex));
	//vertex 번호 입력
	v1->link = NULL;
	v1->num = num1;
	v2->link = NULL;
	v2->num = num2;
	//vertex 연결
	p1->link = v2;
	p2->link = v1;
	return 0;
}

int deleteEdge(Graph* g, int num1, int num2){
	Vertex* p1 = g->vlist[num1].head;
	Vertex* p2;
	while(p1 != NULL && p1->num != num2){ //Edge 존재 확인 + 위치 탐색
		p2 = p1;
		p1 = p1->link;
	}
	if(p1 == NULL){      //없는 Edge인 경우 오류메세지 출력 후 중단
		printf("No Edge!!!\n\n");
		return 0;
	}
	p2->link = p1->link; 
	free(p1);
	p1 = g->vlist[num2].head;
	//(num1)Vertex 의 Edge 제거
	while(p1->num != num1){
		p2 = p1;
		p1 = p1->link;
	}
	p2->link = p1->link;
	free(p1);
	//(num2)Vertex 의 Edge 제거
	return 0;
}

void depthFS(Graph* g, int num){
	Vertex* v = g->vlist[num].head;
	stack[num] = 1;       //받은 번호를 스택에 채움
	printf("[%d]\t", num);  //번호 출력
	while(v){     //처음으로 찾은 Vertex 번호로 계속 탐색
		if(stack[v->num] != 1)
			depthFS(g, v->num);
		v = v->link;
	}
}

void breadthFS(Graph* g, int num){
	Vertex* v = g->vlist[num].head;
	int check = 0;       //큐와 Vertex 번호 비교결과를 결정할 변수
	Queue[++rear] = num; //큐에 Vertex 번호 추가
	while(v){
		while(v){
			for(int i = 0; i<rear+1; i++){
				if(Queue[i] == v->num){  //Vertex 번호와 큐 안의 숫자들 비교
					check = 0;
					break;
				}
				check = 1;
			}
			if(check == 1){   //큐에 없는 번호면 추가
				Queue[++rear] = v->num;
			}
			v = v->link;      //다음 Edge로 이동
		}
		v = g->vlist[Queue[++front]].head; //모든 Edge와 큐 비교후 추가된 번호의 Vertex로 다시 탐색
	}
	front = 0;
	printQueue();  //결과출력
}

void printQueue(){ //큐에 저장된 결과 출력
	while(rear >= front){
		printf("[%d]\t", Queue[front++]);
	}
}

void printGraph(Graph* g){
	printf("Vertex\t    Edge\n=======================================================================\n");
	for(int i = 0; i<MAX_VERTEX; i++){
		if(g->vlist[i].head != NULL){   //존재하는 Vertex의 번호와 Edge 출력
			printf("[%d]\t", i);        //Vertex number
			Vertex* v = g->vlist[i].head; //Edge 탐색할 포인터
			while(v->link != NULL){       //모든 Edge를 찾아서 출력
				printf("    (%d , %d)",i, v->link->num);
				v = v->link;
			}
			printf("\n");
		}
	}
}

void freeVertex(Vertex* v){
	if(v){         //Vertex의 link 존재시 마지막까지 호출하여 할당된 메모리해제
		freeVertex(v->link);
		free(v);
	}
}