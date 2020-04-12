#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int** create_matrix(int row, int col);
int free_matrix(int** matrix, int row, int col);
void print_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int addition_matrix(int **matrix_a, int** matrix_b, int** matrix_sum, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int **matrix_sub, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col);
void error_cancel();

int error = 1;
void main(){
    printf("ID : 2017038059         Name : Bae Gun Young\n"); //학번 이름
    int row, col;           //행, 열의 갯수변수 선언 및 입력
    printf("row : ");
    scanf("%d", &row);
    printf("col : ");
    scanf("%d", &col);
    int **matrix_a = NULL;    //행렬a를 저장할 포인터변수
    int **matrix_b = NULL;    //행렬b
    int **matrix_t = NULL;    //a의 전치행렬
    int **matrix_sum = NULL;  //행렬(a+b)
    int **matrix_sub = NULL;  //행렬(a-b)
    int **matrix_axt = NULL;  //행렬(a*t)
    matrix_a = create_matrix(row, col);       //모든 matrix에 메모리할당
    matrix_b = create_matrix(row, col);
    matrix_t = create_matrix(col, row);       //전치행렬이므로 행과 열의 수를 바꿈
    matrix_sum = create_matrix(row, col);
    matrix_sub = create_matrix(row, col);
    int small;
    if(row > col)
    {                             //a*t행렬은 원래행렬의 행과 열중 더 적은 수치의 n*n행렬으로 생성
        small = col;
    }
    else
    {
        small = row;
    }
    matrix_axt = create_matrix(small, small);
    error = fill_data(matrix_a, row, col); //matrix_a 값 채우기
    error = fill_data(matrix_b, row, col); //matrix_b 값 채우기
    printf("<matrix_a>\n");
    print_matrix(matrix_a, row, col);     //행렬a 출력
    printf("<matrix_b>\n");
    print_matrix(matrix_b, row, col);     //행렬b 출력
    addition_matrix(matrix_a, matrix_b, matrix_sum, row, col);    //a+b계산
    subtraction_matrix(matrix_a, matrix_b, matrix_sub, row, col); //a-b계산
    printf("<matrix(a + b)>\n");
    print_matrix(matrix_sum, row, col);   //행렬(a+b) 출력
    printf("<matrix(a - b)>\n");
    print_matrix(matrix_sub, row , col);  //행렬(a-b) 출력
    transpose_matrix(matrix_a, matrix_t, row, col);  //전치행렬t 값 채우기
    multiply_matrix(matrix_a, matrix_t, matrix_axt, row, col);   //a*t계산
    printf("<matrix_t>\n");                //행렬t 출력
    print_matrix(matrix_t, col, row);
    printf("<matrix_axt>\n");              //행렬axt 출력
    print_matrix(matrix_axt, small, small);
    free_matrix(matrix_a, row, col);      //모든 행렬의 메모리 반납
    free_matrix(matrix_b, row, col);
    free_matrix(matrix_sum, row, col);
    free_matrix(matrix_sub, row, col);
    free_matrix(matrix_t, col, row);
    free_matrix(matrix_axt, small, small);
    printf("free - all matrix\n");           //반납후 값 확인
    printf("matrix_a[0][0] = %d\n",matrix_a[0][0]);
    printf("matrix_axt[0][0] = %d\n",matrix_axt[0][0]);
    printf("Exit program\n");
    exit(0);        //프로그램종료
}   

int fill_data(int** matrix, int row, int col){ //값 채우기 함수
    int i,j;
    for(i=0; i< row; i++){                     //모든행과 열에 0~19 값 배치
        for(j=0; j<col; j++)
            matrix[i][j] = rand()%20;
    }
    if(i == row && j == col)
        error = 1;
    else
        error = -1;
    error_cancel();
    return **matrix;
}

int** create_matrix(int row, int col){       //행렬생성함수
    if(row<1 || col<1) {                     //행이나 열이 1보다 작으면 오류메세지 출력후 에러값 변경
        printf("Cannot make matrix.\n");
        error = -1;
        error_cancel();          //오류시 프로그램 종료
    }
    else{
        int **matrix;
        matrix = malloc(row*sizeof(int*));  //행의 수만큼 메모리할당
        for(int i = 0; i<row; i++){         //matrix[i]에 열의 수만큼 메모리할당(행의 수만큼 반복)
            matrix[i] = malloc(col*sizeof(int**));
        }
    return matrix;            //행렬을 메인으로반환
    }
}

void print_matrix(int** matrix, int row, int col){ //행렬 출력 함수
    int i,j;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){                 //모든행의 모든 열성분 출력
            printf("%d\t",matrix[i][j]);
        }
        printf("\n");                         //한 행을 모두 출력후 줄바꿈
    }
    printf("\n");
    if(i != row || j != col)            //행과 열의 수가 맞지 않으면 에러값 변경후 종료
        error = -1;
    error_cancel();
}

int addition_matrix(int** matrix_a,int** matrix_b, int**matrix_sum, int row, int col){ //행렬 덧셈 함수
    int i,j;
    for (i=0; i<row; i++){
        for(j=0; j<col; j++){
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];  //matrix_sum의 행과열에 a,b의 동일한 행,열의 더한값 입력
        }
    }
    if(i != row || j != col)            //행과 열의 수가 맞지 않으면 에러값 변경
        error = -1;
    else
        error = 1;
    error_cancel();
    return **matrix_sum;
}

int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col){ //행렬 뺄셈 함수
    int i,j;
    for (i=0; i<row; i++){      //a와b의 같은 행,열에 위치한 값끼리 빼서 sub에 저장
        for(j=0; j<col; j++){
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
        }
    }
    if(i != row || j != col)            //행과 열의 수가 맞지 않으면 에러값 변경
        error = -1;
    else
        error = 1;
    error_cancel();
    return **matrix_sub;
}

int transpose_matrix(int** matrix, int** matrix_t, int row, int col){ //전치행렬 함수
    int i,j;
        for(i=0; i<row; i++){         //원래 행렬에 있는값을 행렬t에 행과 열을 바꾸어 입력
            for(j=0; j<col; j++){
                matrix_t[j][i] = matrix[i][j];
            }
        }
    if(matrix_t[col-1][row-1] == matrix[row-1][col-1]){ //원래행렬과 전치행렬의 끝값 비교하여 오류여부확인
        error = 1;
    }
    else
        error = -1;
    error_cancel();
    return **matrix_t;
}


int multiply_matrix(int** matrix_a, int** matrix_t, int ** matrix_axt, int row, int col){ //행렬 곱셈함수
    int i,j,big,small,m,n;
    if(row > col){    //행과 열중 큰 값을 big, 작은값을 small에 저장 (row = column인 경우 big = small)
        big = row;
        small = col;
    }
    else{
        big = col;
        small = row;
    }
    for(m=0; m<small; m++){        //matrix_axt 계산후 값 입력
        for(n=0; n<small; n++){
            matrix_axt[m][n] = 0;
            for(i=0; i<big; i++){
                matrix_axt[m][n] += matrix_a[m][i]*matrix_t[i][n];
            }
        }
    }
    if(m!=n)       //같아야할 m과n의 값 비교하여 error값 반영
        error = -1;
    else
        error = 1;
    error_cancel();
    return **matrix_axt;
}

int free_matrix(int** matrix, int row, int col){
    int i,j;
    j = matrix[0][0];        //메모리반납전 행렬의 첫 값 저장
    for(i=0; i<row; i++){    //행 별로 모든 열의 메모리 반납
        free(matrix[i]);
    }
    free(matrix);            //모든 행의 메모리 반납
    if(matrix[0][0] == j)    //값이 그대로 남아있으면 에러값 변경
        error = -1;
    else
        error = 1;
    error_cancel();
    return **matrix;
}

void error_cancel(){  //오류검사함수
    if (error != 1){  //에러값이 변해서 올경우 오류메세지 출력 후 프로그램 종료
        printf("process canceled by abnormal operation\n");
        exit(0);
    }
}