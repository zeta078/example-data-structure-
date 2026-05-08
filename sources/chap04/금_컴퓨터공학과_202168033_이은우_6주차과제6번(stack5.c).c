/*
프로그램 일시 : 2026.04.10
작성자 : 이은우
코드 파일 이름 : 금_컴퓨터공학과_202168033_이은우_6주차과제6번(stack5.c).c
작업 제목 : malloc과 realloc을 활용한 스택 프로그램
원본 코드 : chap04/stack5.c
etc1 : 6주차 과제 6번 코드
etc2 : 변수명 변경
etc3 : 본인만의 주석 처리
*/

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
	element *data;		// data은 포인터로 정의된다.
	int capacity;		// 현재 크기
	int top;
} StackType;

// 스택 생성 함수
// malloc을 사용하는 이유 : 스택의 크기를 동적으로 할당하기 위해서 초기에는 작은 크기로 시작하지만, 필요에 따라 크기를 늘릴 수 있다.
void init_stack(StackType *s)
{
	s->top = -1;
	s->capacity = 100;
	s->data = (element *)malloc(s->capacity * sizeof(element));
}

// 공백(빈 : empty) 상태 검출 함수
int stk_emp(StackType *s)
{
	return (s->top == -1);
}
// 포화(가득 찬 :full) 상태 검출 함수
int stk_ful(StackType *s)
{
	return (s->top == (s->capacity - 1));
}
void push(StackType *s, element item)
{
	if (stk_ful(s)) {
		s->capacity *= 2;
		s->data =
			// realloc을 사용하는 이유 : 스택이 가득 찼을 때, 기존의 크기를 두 배로 늘려서 더 많은 요소를 저장할 수 있도록 한다.
			(element *)realloc(s->data, s->capacity * sizeof(element));
	}
	s->data[++(s->top)] = item;
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
int main(void)
{
	StackType s;
	init_stack(&s);		// 스택 초기화
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);

	printf("%x\n", &s);			// 스택 주소(16진수)
	printf("%d \n", pop(&s));	// 스택 내용

	printf("%x\n", &s);			// 스택 주소(16진수)
	printf("%d \n", pop(&s));	// 스택 내용

    printf("%x\n", &s);			// 스택 주소(16진수)
	printf("%d \n", pop(&s));	// 스택 내용
	free(s.data);
	/*
	free를 사용하는 이유 : 동적으로 할당된 메모리를 해제하여 메모리 누수를 방지하기 위해서 
	스택이 더 이상 필요하지 않을 때, 할당된 메모리를 반환하는 것이 좋음
	*/
	return 0;
}

/*
결론 : malloc과 realloc를 쓰는 이유는 고정된 크기가 아닌 동적 크기의 스택을 구현하기 위함이다.
free를 함께 씀으로써 동적으로 관리된 메모리 크기를 효율적으로 관리할 수 있다.
*/