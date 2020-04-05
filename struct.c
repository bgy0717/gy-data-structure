#include<stdio.h>
#include<string.h>

struct person_a{   //struct 선언
    char name[10];     //이름
    int age;           //나이
    char hobby[10];    //취미
};

typedef struct {   //typedef struct 선언
    char name[10];     //이름
    int age;           //나이
    char hobby[10];    //취미
}person_b;

int main(){
    struct person_a p1= {"Park", 22, "baseball"}; //첫번째 사람
    person_b p2 = {"Hong", 17, "game"};           //두번째 사람
    person_b p3;                                  //세번째 사람
    p3 = p2;   //세번째 사람에게 두번째 사람과 같은정보 입력

    printf("<person 1>\n");             //첫번째
    printf("name \t: %s\n",p1.name);    //이름출력
    printf("age \t: %d\n",p1.age);      //나이출력
    printf("hobby \t: %s\n",p1.hobby);  //취미출력

    printf("<person 2>\n");             //위와같음
    printf("name \t: %s\n",p2.name);
    printf("age \t: %d\n",p2.age);
    printf("hobby \t: %s\n",p2.hobby);

    printf("<person 3>\n");             //위와같음
    printf("name \t: %s\n",p3.name);
    printf("age \t: %d\n",p3.age);
    printf("hobby \t: %s\n",p3.hobby);

    if(strcmp(p2.name , p3.name)==0 && p2.age == p3.age && strcmp(p2.hobby , p3.hobby)==0) //p2와 p3가 같다면
        printf("p2 == p3\n");                                                              //p2 == p3 출력
    else                            //다르다면
        printf("p2 != p3\n");       //p2 != p3 출력

    return 0;
}