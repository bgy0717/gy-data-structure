#include<stdio.h>

void printa(int *ptr, int n);     //출력함수선언

int main(){
    int arr[] = {0, 1, 2, 3, 4};         //크기5인 배열선언
    printf("< address >\n");             //주소
    printf("arr\t = %p\n",arr);          //arr(=arr[0])의 주소
    printf("&arr\t = %p\n",&arr);        //arr(=arr[0])의 주소
    printf("&arr[0]\t = %p\n",&arr[0]);  //arr[0]의 주소
    printa(&arr[0], 5); //출력함수 실행
    return 0;
}

void printa(int *ptr, int n){                //출력함수정의
    printf("address \t contents\n");         //주소 내용 구분
    for(int i=0;i<n;i++){                    //n번 실행
        printf("%p \t %d\n",ptr+i,*(ptr+i)); //ptr+i가 가르키는 주소, 값 출력
    }
}