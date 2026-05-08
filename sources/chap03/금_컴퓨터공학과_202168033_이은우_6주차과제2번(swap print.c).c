/*
프로그램 일시 : 2026.04.10
작성자 : 이은우
코드 파일 이름 : 금_컴퓨터공학과_202168033_이은우_6주차과제2번(swap print.c)
작업 제목 : 포인터를 활용한 swap 프로그램
원본 코드 : chap03/swap.c
etc1 : 6주차 과제 2번 코드
etc2 : 코드 흐름 확인을 위한 각 줄마다 printf문 추가
etc3 : 공백
*/

#include <stdio.h>
/*
swap 함수 : 두 변수의 값을 서로 교환하는 함수
포인터를 사용해서 실제 변수의 값을 직접 바꾼다.
매개변수로 int형 포인터 px와 py를 받는다.
*/ 
void swap(int *px, int *py)
{
	printf("==============================\n");
	printf("[swap 시작] *px=%d, *py=%d\n", *px, *py);	// swap 함수가 시작될 때 *px와 *py의 값을 출력한다. (처음에는 *px=1, *py=2가 출력될 것이다.)
	
	int tmp;	// tmp는 swap 과정에서 임시로 값을 저장하는 변수이다.
	tmp = *px; 	// tmp에 *px의 값을 저장한다. (tmp는 이제 *px의 값을 가지고 있다.)
	printf("tmp = *px -> tmp=%d\n", tmp);

	*px = *py;  // *px에 *py의 값을 저장한다. (이제 *px는 *py의 값을 가지고 있다.)
	printf("*px = *py -> *px=%d\n", *px, *py);
	
	*py = tmp;	// *py에 tmp의 값을 저장한다. (이제 *py는 tmp의 값을 가지고 있다. 즉, 원래 *px의 값이 *py로 이동했다.)
	printf("*py = tmp -> *py=%d\n", *py);

	printf("[swap 종료]\n");
	printf("==============================\n");
}

int main(void)
{
	int a = 1, b = 2;
	printf("swap을 호출하기 전: a=%d, b=%d\n", a, b);	// swap 함수를 호출하기 전에 a와 b의 값을 출력한다. (a=1, b=2가 출력될 것이다.)
	printf("swap 호출!!\n");
	swap(&a, &b);
	printf("swap을 호출한 다음: a=%d, b=%d\n", a, b); 	// swap 함수를 호출한 다음에 a와 b의 값을 출력한다. (a=2, b=1이 출력될 것이다.)
	return 0;
}