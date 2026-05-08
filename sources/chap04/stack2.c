/*
프로그램 일시 : 2026.04.10
작성자 : 이은우
작업 제목 : 구조체를 활용한 스택 프로그램
원본 코드 : stack2.c
기타 : 5주차 과제 2번 코드
기타2 : push, pop에 대한 변수 수정
etc : 공백
*/

#include <stdio.h>
#include <stdlib.h>

//전역변수
#define MAX_STACK_SIZE 100 //스택의 최대 크기
#define MAX_STRING 100 //문자열의 최대 크기
typedef struct {
	int student_no;
	char name[MAX_STRING];
	char address[MAX_STRING];
} element;
element  stack[MAX_STACK_SIZE];
int  top = -1;

// 공백(빈 : empty) 상태 검출 함수
int str_empty()
{
	return (top == -1);
}
// 포화(가득 찬 : full) 상태 검출 함수
int str_full()
{
	return (top == (MAX_STACK_SIZE - 1));
}
// 삽입(push())함수
void push(element item)
{
	if (str_full()) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else stack[++top] = item;
}
// 삭제(pop()) 함수
element pop()
{
	if (str_empty()) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return stack[top--];
}
// 피크 함수
element peek()
{
	if (str_empty()) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return stack[top];
}

// 메인 함수
int main(void)
{
	// 5명의 학생 정보를 ie 구조체 변수에 초기화
	element ie[5] = {
		{20190001, "Hong", "Soeul"},
		{20190002, "kim", "Busan"},
		{20200010, "Lee", "Incheon"},
		{202168033, "Lee", "Wanju"},
		{202345003, "Park", "Gwangju"}
		};
	// 결과를 저장할 구조체 변수 선언
	element oe;

	for (int i = 0; i < 5; i++) {
		push(ie[i]);	// ie[i] 데이터를 스택에 삽입
	}

	for (int i = 0; i < 5; i++) {
		oe = pop(); //스택에서 데이터를 꺼내 oe에 저정
	printf("===========================================\n");
	printf("학번: %d\n", oe.student_no);
	printf("이름: %s\n", oe.name);
	printf("주소: %s\n", oe.address);
	printf("===========================================\n");
	}
	
	return 0;
}