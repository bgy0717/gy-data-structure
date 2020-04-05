#include<stdio.h>

typedef struct {    //구조체선언
    char name[17];  //17byte크기의 char형 변수
    int age;        //int형 변수
    double score;   //double형 변수
}person;            //구조체명

int main(){
    person p1;     //구조체변수 추가

    printf("<size>\n");                           //크기를 출력함
    printf("person \t= %d\n", sizeof(person));    //구조체 person의 크기
    printf("p1 \t= %d\n", sizeof(p1));            //구조체변수 p1의 크기
    printf("name[17]= %d\n", sizeof(p1.name));    //p1.name 크기
    printf("char \t= %d\n", sizeof(char));        //char타입의 크기
    printf("double \t= %d\n", sizeof(double));    //double타입의 크기

    return 0;
}