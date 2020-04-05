#include<stdio.h>
#include<stdlib.h>

int main(){
    int a[5];   //5자리 배열
    a[0]=10;
    a[1]=15;

    int n;
    printf("a[0]\t=%d\n", a[0]);    //a[0]의 값
    printf("&a\t=%p\n",&a);         //a의 주소(=a[0]의 주소)
    printf("&a[0] = %p\n",&a[0]);   //a[0]의 주소
    for(n=0;n<5;n++){                         //a[0]부터 a[4]까지
        printf("a + %d = %p\n",n,a+n);        //a + n의 주소(= a[n]의 주소)
        printf("*(a + %d) = %d\n",n, *(a+n)); //a[n]의 값 (a[2] ~ a[4] : 쓰레기값)
    }
    printf("a[4] = %p\n",&a[4]);    //a[4]의 주소

    return 0;
}