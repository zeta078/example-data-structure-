/*
프로그램 일시 : 2026.05.03
작성자 : 이은우
작업 제목 : 원형 큐 프로그램
원본 코드 : cir_queue.c
기타1 : 9주차 과제 2번 코드
기타2 : 각 함수에서 동작 과정과 상태를 출력하도록 디버깅 메시지(printf문) 추가
기타3 : 본인의 공부와 이해를 돕기 위한 상세 주석 추가
etc : 공백 
*/

// 원형큐
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 5		// 큐의 최대 크기 5
typedef int element;
typedef struct { 				// 큐 타입
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;			// 출구, 입구 인덱스
} QueueType;

// 오류 (error)함수 : 오류 메시지를 출력 후 프로그램을 종료
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 공백 상태 검출 (init_queue)함수 : 큐를 초기화
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;		//선형큐와 초기값 설정이 구조상 다르다.
	// 원형 큐는 front와 rear를 같은 위치(0)로 시작 -> 공백 상태 의미
	printf("[init : 초기화] front = %d, rear = %d\n", q->front, q->rear);
}

// 공백 상태 검출 (is_empty)함수 : 큐가 비어 있는지 검사
int is_empty(QueueType *q)
{
	// front == rear -> 데이터가 하나도 없는 (공백 상태
	if (q->front == q->rear) {	//front = rear인 경우 삽입된 데이터가 없는 공백 상태
		printf("[is_empty : 공백 상태 확인] front -- rear -- %d -> 공백 상태!\n", q->front);
		return 1;
	}
	else{
		printf("[is_empty : 공백 상태 확인] front = %d, rear = %d -> 비어 있지 않음\n", q->front, q->rear);
		return 0;
	}
	return 0;
}

// 포화 상태 검출 (is_full)함수 : 큐가 포화 상태인지 검사
int is_full(QueueType *q)
{
	// rear 다음 위치가 front와 같으면 -> 더 이상 삽입 불가
	if ((q->rear + 1) % MAX_QUEUE_SIZE == q->front) {
		printf("[is_full : 포화 상태 확인] front = %d, rear = %d -> 포화 상태!\n", q->front, q->rear);
		return 1;
	}
	else {
		printf("[is_full : 포화 상태 확인] front = %d, rear = %d -> 포화 상태 아님\n", q->front, q->rear);
		return 0;
	}
}

// 원형큐 출력 (queue_print)함수
void queue_print(QueueType *q)
{
	printf("QUEUE(front=%d rear=%d)\n", q->front, q->rear);
	printf("Queue[data] = | ");

	// 공백이 아닐 때만 출력
	if (q->front != q->rear) {
			int i = q->front;
			do {
				// 원형 구조이므로 인덱스를 1 증가 후 나머지 연산
				i = (i + 1) % (MAX_QUEUE_SIZE);
				printf("%d | ", q->data[i]);

				// rear까지 출력하면 종료
				if (i == q->rear)
					break;
			} while (i != q->front);
		}
	printf("\n");
}

// 삽입 (enqueue)함수
void enqueue(QueueType *q, element item)
{
	printf("\n[enqueue : 삽입] item = %d 삽입 시도\n", item);

	// 포화 상태이면 삽입 불가
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	printf("[enqueue : 삽입] rear 증가: %d -> %d\n", q->rear - 1, q->rear);

	// 이동된 위치에 데이터 저장
	q->data[q->rear] = item;
	printf("[enqueue : 삽입] data[%d] -> %d 저장 완료\n", q->rear, item);
}

// 삭제 (dequeue)함수
element dequeue(QueueType *q)
{
	// 공백  상태이면 삭제 불가
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	printf("[dequeue : 삭제] front 증가: %d -> %d\n", q->front - 1, q->front);

	// 이동된 위치에 데이터 반환
	printf("[dequeue : 삭제] data[%d] = %d 삭제 완료\n", q->front, q->data[q->front]);
	return q->data[q->front];
}

// 조회 (peek)함수
element peek(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	
	// front 다음 위치가 실제 첫 데이터
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ===== 원형큐 코드 끝 ======

// 메인 (main)함수 
int main(void)
{
	QueueType queue;
	int element;
	char choice; // 사용자 입력을 위한 변수

	init_queue(&queue);

	printf("--데이터 추가 단계--\n");

	// 포화 상태가 될 때까지 입력
	while (!is_full(&queue))
	{
		printf("정수를 입력하시오: ");
		scanf("%d", &element);

		enqueue(&queue, element);
		queue_print(&queue);
	}

	printf("현재 큐가 포화상태입니다.\n");

	// 현재 원형 큐가 포화 상태인 경우 삭제 단계로 이동할지 사용자에게 묻기
	printf("\n삭제 단계로 이동하시겠습니까? (y/n): ");
	scanf(" %c", &choice);   // 앞의 공백은 이전 입력의 엔터를 무시하기 위함

	if (choice == 'y' || choice == 'Y') {
		printf("\n--데이터 삭제 단계--\n");

		// 공백이 될 때까지 삭제
		while (!is_empty(&queue))
		{
			element = dequeue(&queue);
			printf("꺼내진 정수: %d \n", element);
			queue_print(&queue);
		}

		printf("삭제 단계로 인해서 현재 큐는 공백상태입니다.\n");
	}
	else {
		printf("삭제하지 않고 프로그램을 종료합니다.\n");
	}

	return 0;
}