/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;           //커맨드 입력 변수
	int *array = NULL;      //배열
	int *hashtable = NULL;  //해쉬테이블
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)    //원소 존재시 할당된 메모리 해제
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {    //원소가 없는경우 메세지 출력 후 함수 종료
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //배열에서의 위치 출력
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //위치에서의 값 출력
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬되기 전의 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++) //i번째 값부터 끝까지 비교해가며 i번째 값을 최솟값으로 변경
	{
		minindex = i; //i번을 최솟값의 위치로 임시지정
		min = a[i];   //i번째 값을 최솟값으로 임시지정
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //i번째 값과 그 뒤의 모든 값을 비교
		{
			if (min > a[j]) //최솟값보다 작으면 그 값을 최솟값으로 바꿔가며 탐색
			{
				min = a[j]; //최솟값으로 저장해둠
				minindex = j; //최솟값의 위치
			}
		}
		a[minindex] = a[i]; //최솟값이었던 위치의 값을 배열의 i번째 값으로 변경
		a[i] = min;         //i번째 값을 찾은 최솟값으로 변경
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬된 배열 출력ㅂ
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬하기 전 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++) //a[01]부터 시작해서 a[12]까지의 값들을 자신보다 앞에 존재하는 더 작은 값이 나올 때 까지 비교
	{
		t = a[i];  //비교할 값
		j = i; 
		while (a[j-1] > t && j > 0) //비교할 값보다 작은 값이 나올 때까지 반복
		{
			a[j] = a[j-1]; //앞의 값을 뒤로 옮김
			j--;           //한 칸 내려가서 비교하도록 함
		}
		a[j] = t; //멈춘 위치의 값을 비교해온 값으로 변경
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬된 배열 출력

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)      //배열 크기만큼 반복
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++) //배열의 처음부터 끝까지 순회
		{
			if (a[j-1] > a[j]) //앞의 원소가 바로뒤의 원소보다 더 크면 서로 교환
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬된 배열 출력

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬전 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //비교간격을 좁혀가며 반복
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; //비교할 뒤쪽의 값
				k = j;    //뒤쪽의 값의 위치
				while (k > h-1 && a[k-h] > v) //앞쪽의 값이 더 크면 뒤의 값을 큰 값으로 바꾸고 k를 앞쪽갚으로 위치
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v; //앞의 값을 뒤에있던 값으로 변경
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬된 배열 출력

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; //pivot값
		i = -1;     //배열의 앞부분
		j = n - 1;  //배열의 뒷부분

		while(1)
		{
			while(a[++i] < v); //앞쪽에서부터 pivot 보다 큰 값 찾기
			while(a[--j] > v); //뒷쪽에서부터 pivot 보다 작은값 찾기

			if (i >= j) break; //i, j 의 위치가 같거나 앞뒤가 바뀌었으면 중단
			t = a[i];     //i, j 위치의 값 교환
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];     //i 위치의 값과 pivot 값 교환
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);           //i기준으로 배열을 나눠서 각각 퀵 정렬 실행
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //key값을 해쉬테이블에 들어갈 번호로 리턴
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);  //입력받은 key값을 해쉬코드로 변환하여 index에 저장

	if(ht[index] == key)  //해쉬테이블의 index 위치에 key값이 있으면 위치값 리턴
		return index;

	while(ht[++index] != key) //index값을 증가시켜가며 해쉬테이블 탐색
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index; //반복문 탈출 후 index값 리턴
}



