#include<stdio.h>
#define SIZE 101

float sum(float [],int);   //sum함수 선언
float input[SIZE], answer; //101개의 배열, 전역변수 answer선언
int i;  //전역변수

void main(){
    for(i=0;i<SIZE;i++)  //101번 반복
        input[i] = i;
    printf("input(address) = %p\n",input); //input의 주소
    answer = sum(input, SIZE);             //sum함수 실행 후 answer에 값 반환
    printf("sum = %f\n",answer);           //합계 출력
}

float sum(float list[], int n){           //sum함수 정의
    printf("list(address) = %p\n",list);  //list가 가르키는 주소(input)
    printf("&list = %p\n",&list);         //list의 주소

    float temp = 0;     //값의 임시저장변수
    for(i=0;i<n;i++)    //101번반복
        temp +=list[i]; //temp에 0~100의 합 저장
    return temp;        //더한값을 반환
}