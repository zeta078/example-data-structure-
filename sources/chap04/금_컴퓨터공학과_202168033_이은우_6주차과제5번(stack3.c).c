/*
프로그램 일시 : 2026.04.10
작성자 : 이은우
코드 파일 이름 : 금_컴퓨터공학과_202168033_이은우_6주차과제5번(stack3.c).c
작업 제목 : 구조체와 포인트를 활용한 스택 프로그램
원본 코드 : chap04/stack3.c
etc1 : 6주차 과제 5번 코드
etc2 : 출력문에 16진수 스택 주소값 추가
etc3 : 변수명 변경
*/

#include <stdio.h>
#include <stdlib.h>

// 차후에 스택이 필요하면 여기만 복사하여 붙인다.
// ===== 스택 코드의 시작 =====
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top; //시험 출제 빈칸 및 의미 쓰기
} StackType;

// 스택 초기화 함수
void init_stack(StackType *s)
{
	s->top = -1;	//시험
}

// 공백 상태 검출 함수
int stk_emp(StackType *s)
{
	return (s->top == -1); //시험
}
// 포화 상태 검출 함수
int stk_ful(StackType *s) 	//StackType *s에 부분에 변수명 변경해서 출제
{
	return (s->top == (MAX_STACK_SIZE - 1)); 	//MAX_STACK_SIZE - 1은 스택의 최대 인덱스 번호를 의미한다. 시험
}
// 삽입함수
void push(StackType *s, element item)
{
	if (stk_ful(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;  //++, -- 연산자 위치에 따른 차이 출제
}
// 삭제함수
element pop(StackType *s)
{
	if (stk_emp(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// 피크함수
element peek(StackType *s)
{
	if (stk_emp(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 


int main(void)
{
	StackType s;

	init_stack(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);

	printf("%x\n", &s);			// 스택 주소(16진수)
	printf("%d\n", pop(&s));	// 스택 내용
	printf("%x\n", &s);			// 스택 주소(16진수)
	printf("%d\n", pop(&s));	// 스택 내용
	printf("%x\n", &s);			// 스택 주소(16진수)
	printf("%d\n", pop(&s));	// 스택 내용
}
