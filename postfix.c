/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixPush(char x) //postfix의 Push함수
{
    postfixStack[++postfixStackTop] = x;     //postfix스택의 Top위치 변경하고 그 위치에 x저장
}

char postfixPop()       //postfix의 Pop함수
{
    char x;             //문자하나를 저장할 변수
    if(postfixStackTop == -1)      //스택이 비어있으면 공백 반환
        return '\0';
    else {                                   //스택에 값이있으면
    	x = postfixStack[postfixStackTop--]; //x에 top의 문자를 저장하고 top의 위치를 내림
    }
    return x; //pop하여 빼낸 문자 반환
}


void evalPush(int x) //eval의 push함수
{
    evalStack[++evalStackTop] = x;  //eval스택의 top위치 변경후 그 위치에 x저장
}

int evalPop() //eval의 pop함수
{
    if(evalStackTop == -1) //스택이 빔
        return -1;         //-1반환
    else                                  //스택에 내용 있음
        return evalStack[evalStackTop--]; //pop된 수치 반환후 top위치 내림
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}

}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	int y;
	char a = *exp;
	int postfixExpTop = -1;  //postfix로 옮겨진 문자열의 끝값 위치 초기화 및 선언
	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		x = *exp++;          //exp가 가리키는 문자를 가져오고 exp는 다음문자 지시
		y = getToken(x);     //exp에서 가져온 문자의 토큰 변수
		if(y == 7)           //곱셈,나눗셈 우선순위 동일취급
			y = 6;
		if(y == 5)           //덧셈,뺄셈 우선순위 동일취급
			y = 4;
		if(y == 1)           //가져온 문자가 operand인 경우
			postfixExp[++postfixExpTop] = x;                     //그대로postfix에 추가
		else if(postfixStackTop == -1) //x가 연산자이고 스택이 비어있으면
			postfixPush(x);            //x를 push
		else if(y == 9) {                                        //닫는 괄호인 경우
			while(getToken(postfixStack[postfixStackTop]) != 0){ //스택의 탑의 문자가 여는괄호가 나올때까지
				postfixExp[++postfixExpTop] = postfixPop();      //사이의 문자들을 pop하여 postfix에 추가
			}
			postfixPop();   //여는 괄호는 postfix에 저장하지않고 그대로 pop
		}
		else if(y == 0 || y > getToken(postfixStack[postfixStackTop])) //여는 괄호나 우선순위 높은 연산자
			postfixPush(x); //x를 그대로 push
		else if(y <= getToken(postfixStack[postfixStackTop])){ //x가 스택의 탑보다 우선순위 작거나 같은 연산자
			postfixExp[++postfixExpTop] = postfixPop();        //하나만 pop하여 postfix에 추가
			postfixPush(x); //x는 push
		}
	}   //exp의 문자열을 모두 읽음
	while(postfixStack[postfixStackTop] != '\0')   //스택이 빌 때까지
		postfixExp[++postfixExpTop] = postfixPop();//스택을 전부 pop하고 postfix에 추가
}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);     //infix수식 출력
	printf("postExp =  %s\n", postfixExp);    //postfix수식 출력
	printf("eval result = %d\n", evalResult); //계산결과 출력

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)  //스택 출력
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()            //리셋함수
{
	infixExp[0] = '\0';    //infix수식 초기화
	postfixExp[0] = '\0';  //postfix수식 초기화

	for(int i = 0; i < MAX_STACK_SIZE; i++) //스택 내의 내용 초기화
		postfixStack[i] = '\0';
         
	postfixStackTop = -1; //각 스택의 탑, 계산결과 초기화
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
	char* exp = postfixExp; //postfix수식 지시 포인터
	char x = *exp++;        //exp의 한 문자를 저장할 변수
	int calc;               //계산결과를 저장할 변수
	int temp;               //pop한 숫자를 잠시 저장할 변수
	evalPush((int)x-48); //postfix의 첫값은 무조건 숫자이므로 push
	while(*exp != '\0'){  //문자열이 끝날 때까지
		x = *exp++;       //x에 문자하나 넣고 포인터 이동
		int value = (int)x-48;       //operand x를 int 타입 수치로 저장해둘 변수
		switch (getToken(x))         //x의 토큰에 대해서 스위치문
		{
		case operand:                   //수치가 올 경우
			evalPush(value);            //그대로 push
			break;
		case plus:                      //덧셈
			calc = evalPop()+evalPop(); //스택에서 뒤의 두 수를pop 하여 덧셈
			evalPush(calc);             //덧셈결과 push
			break;
		case minus:                     //뺄셈
			temp = evalPop();           //먼저 스택의 top을 pop
			calc = evalPop()-temp;      //하나더 pop하여 temp와 뺄셈
			evalPush(calc);             //뺄셈결과 push
			break;
		case times:                     //곱셈
			calc = evalPop()*evalPop(); //두 수를 pop하여 곱셈
			evalPush(calc);             //곱셈결과 push
			break;
		case divide:                    //나눗셈
			temp = evalPop();           //스택의 top을 pop하여 저장
			calc = evalPop()/temp;      //하나더 pop하고 temp로 나눔
			evalPush(calc);             //나눗셈결과를 push
			break;
		default:
			break;
		}
	}
	evalResult = evalPop();     //스택에 남아있는 연산결과 반환
}


int main()
{
	printf("id : 2017038059\t\tname : Bae Gun Young\n");
	char command;     //명령을 받을 변수

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //명령 입력

		switch(command) {       //명령에 따른 스위치문
		case 'i': case 'I':     //Infix 선택시
			getInfix();         //수식입력 함수 실행
			break;
		case 'p': case 'P':     //Postfix 선택시
			toPostfix();        //Infix에 저장되어있는 수식을 postfix화 하는 함수 실행
			break;
		case 'e': case 'E':     //Eval 선택
			evaluation();       //postfix에 저장된 수식을 이용해 계산하는 함수 실행
			break;
		case 'd': case 'D':     //Debug 선택
			debug();            //디버그 함수 실행
			break;
		case 'r': case 'R':     //Reset 선택
			reset();            //리셋 함수 실행
			break;
		case 'q': case 'Q':
			break;
		default:                //잘못 입력시
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //오류메세지 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); //Quit 선택 전까지 반복

	return 0;


}
