#include<stdio.h>
#include<stdlib.h>

void main(){
    int **x;     //int형 이중포인터 선언
    double **y;  //double형 이중포인터 선언

    printf("<sizeof>\n");  //size를 출력할것
    printf("x \t= %d\n",sizeof(x));     //x가 가르키는 주소의 크기
    printf("*x \t= %d\n",sizeof(*x));   //*x의 값(address)의 크기
    printf("**x \t= %d\n",sizeof(**x)); //**x의 값(value)의 크기

    printf("y \t= %d\n",sizeof(y));     //y가 가르키는 주소의 크기
    printf("*y \t= %d\n",sizeof(*y));   //*y의 값(address)의 크기
    printf("**y \t= %d\n",sizeof(**y)); //**y의 값(value)의 크기
}