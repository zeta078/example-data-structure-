/*
프로그램 일시 : 2026.04.03
작성자 : 이은우
작업 제목 : 전역변수를 활용한 스택 프로그램
etc1 : 5주차 과제 1번 코드
etc2 : push, pop에 대한 변수 수정
etc3 : 공백
*/

#include <stdio.h>
#include <stdlib.h>

//전역변수
#define MAX_STACK_SIZE 100	// 스택의 최대 크기
typedef int jju_element;		// 데이터의 자료형
jju_element  stack[MAX_STACK_SIZE]; // 1차원 배열
int  top = -1;

// 공백(빈 : empty) 상태 검출 함수
int stk_emp()
{
	return (top == -1);
}
// 포화(가득 찬 : full) 상태 검출 함수
int stk_ful()
{
	return (top == (MAX_STACK_SIZE - 1));
}
// 삽입(push()) 함수
void push(jju_element item)
{
	if (stk_ful()) {
		fprintf(stderr, "스택 포화 에러(비우셔야 합니다!)\n");
		return;
	}
	else stack[++top] = item;
}
// 삭제(pop()) 함수
jju_element pop()
{
	if (stk_emp()) {
		fprintf(stderr, "스택 공백 에러(현재 스택이 비어있습니다.)\n");
		exit(1);
	}
	else return stack[top--];
}
// 피크 함수 (스택을 체크하는 함수)
jju_element peek()
{
	if (stk_emp()) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return stack[top];
}

int main(void)
{
	push(1);
	push(2);
	push(3);
	push(4);
	push(5);

	printf("===========================================\n");
	printf("스택의 최상단 원소 : %d\n", peek()); // 스택의 최상단 원소 출력
	printf("===========================================\n");
	//스택 출력문
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	return 0;
}