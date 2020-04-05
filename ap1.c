#include<stdio.h>
#include<stdlib.h>

int main(){
	int a[5];                          //배열선언
	int *pa[5]={NULL,};                //포인터배열을 NULL값으로 초기화
    pa[0]=(int*)malloc(sizeof(int));   //pa[0]에 int크기만큼 메모리 할당

	a[0]=10;
	a[1]=30;
	*pa[0]=2000;          //pa[0]이 가르키는값에 2000

	int n=0;
	for(n=0 ; n<2 ; n++){                   //a[0]부터 a[1]까지
		printf("a[%d] = %d\n",n,a[n]);      //a[n]의 값
		printf("&a[%d] = %p\n",n,&a[n]);    //a[n]의 주소
		printf("*(a+%d) = %d\n",n,*(a+n));  //a+n(a[0], a[1])의 값
		printf("a+%d = %p\n\n",n,a+n);      //a+n의 주소
	}
	printf("*pa[0] = %d\n",*pa[0]);         //pa[0]의 가르키는 값
	printf("&pa[0] = %p\n", &pa[0]);        //pa[0]의 주소
	printf("&pa = %p\n", &pa);              //pa[0]의 주소
	printf("pa = %p\n", pa);                //pa[0]의 주소
	for(n=0 ; n<5; n++){                   //pa[0]부터 pa[4]까지
		printf("pa[%d] = %p\n",n,pa[n]);   //pa[n]의 주소 출력
	}
	return 0;
}