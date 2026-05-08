/*
프로그램 일시 : 2026.05.03
작성자 : 이은우
작업 제목 : 선형 큐 프로그램
원본 코드 : linear_queue.c
기타1 : 9주차 과제 1번 코드
기타2 : 각 함수에서 동작 과정과 상태를 출력하도록 디버깅 메시지(printf문) 추가
기타3 : 본인의 공부와 이해를 돕기 위한 상세 주석 추가
etc : 공백
*/

/*
선형 큐 : rear가 배열의 마지막 위치에 도달하면,
		앞쪽 공간이 비어 있어도 다시 사용할 수 없다.
*/

#include <stdio.h>
#include <stdlib.h>

// ===== 선형 큐 코드 시작 =====
#define MAX_QUEUE_SIZE 5			//큐의 최대 크기 5
typedef int element;
typedef struct { 					// 큐 타입
	int  front;						// 출구 인덱스 : 마지막으로 삭제된 데이터의 위치기억
	int rear;						// 입구 인덱스 : 마지막으로 삽입된 데이터의 위치기억
	element  data[MAX_QUEUE_SIZE];	//데이터 저장소 : 실제 데이터 저장 공간
} QueueType;

// 오류 (error)함수 : 오류 메시지를 출력 후 프로그램을 종료
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//큐 초기화 (init_queue)함수 : 큐를 초기화
void init_queue(QueueType *q)
{
	// front와 rear를 -1로 초기화하여 큐가 비어 있음을 나타냄
	q->rear = -1;
	q->front = -1;
	printf("[init : 초기화] front = %d, rear = %d\n", q->front, q->rear);
}

// 공백 상태 확인 (is_empty)함수 : 큐가 비어 있는지 검사
int is_empty(QueueType *q)
{
	if (q->front == q->rear) {	//front = rear인 경우 삽입된 데이터가 없는 공백 상태
		printf("[is_empty : 공백 상태 확인] front --rear -- %d -> 공백 상태!\n", q->front);
		return 1;
	}
	else{
		printf("[is_empty : 공백 상태 확인] front = %d, rear = %d -> 비어 있지 않음\n", q->front, q->rear);
		return 0;
	}
}

//포화 상태 확인 (is_full)함수 : 큐가 포화 상태인지 검사
int is_full(QueueType *q)
{
	// rear가 MAX_QUEUE_SIZE - 1인 경우 큐가 포화 상태임
	if (q->rear == MAX_QUEUE_SIZE - 1){
		printf("[is_full : 포화 상태 확인] rear = %d -> 포화 상태!\n", q->rear);
		return 1;
	}
	else {
		printf("[is_full : 포화 상태 확인] rear = %d -> 포화 상태 아님\n", q->rear);
		return 0;
	}
}

//큐 상태 출력 (queue_print)함수 : 큐의 현재 상태를 출력
void queue_print(QueueType *q)
{
	printf("[state : 상태 출력] front = %d, rear = %d  \nQueue[data] = | ", q->front, q->rear);
	for (int i = 0; i<MAX_QUEUE_SIZE; i++) {
		// front 이하 영역은 이미 삭제된 데이터 영역
		// rear 초과 영역은 아직 삽입되지 않은 빈 공간
		if (i <= q->front || i> q->rear)
			printf("   | ");
		else
			printf("%d | ", q->data[i]);
	}
	printf("\n");
}

//삽입 (enqueue)함수 : 큐에 요소를 삽입
void enqueue(QueueType *q, int item)
{
	printf("[enqueue : 삽입] item = %d 삽입 시도\n", item);
	
	// 포화 상태라면 삽입 불가 
	if (is_full(q)) {
		error("큐 포화 상태");
		return;
	}
	//q->data[++(q->rear)] = item;    	//rear 값은 먼저 1 증가시킴(-1 -> 0) 후에 item 저장

	// rear는 마지막 삽입 위치이므로 먼저 1 증가시켜 새로운 위치 확보 
	q->rear++;
	printf("[enqueue : 삽입] rear 증가 : %d -> %d\n", q->rear - 1, q->rear);
	
	// 증가된 위치에 데이터 저장
	q->data[q->rear] = item;
	printf("[enqueue : 삽입] data[%d] -> %d 저장 완료\n", q->rear, item);
}

//삭제 (dequeue)함수 : 큐에서 요소를 삭제
int dequeue(QueueType *q)
{
	// 공백 상태라면 삭제 불가 
	if (is_empty(q)) {
		error("큐 공백 상태.");
		return -1;
	}
	//int item = q->data[++(q->front)];	//front 값을 먼저 1 증가시킴(-1 -> 0) 후에 item 저장

	// front는 마지막 삭제 위치이므로 먼저 1 증가시켜 실제 삭제 위치로 이동
	q->front++;
	printf("[dequeue : 삭제] front 증가: %d -> %d\n", q->front - 1, q->front);
	
	// 해당 위치의 데이터 반환
	int item = q->data[q->front];
	printf("[dequeue : 삭제] data[%d] - %d 반환 완료\n", q->front, item);
	return item;
}

// 메인 (main)함수
int main(void)
{
	int item = 0;
	QueueType q;

	init_queue(&q);
	printf("=====================================\n");

	enqueue(&q, 10); queue_print(&q);
	enqueue(&q, 20); queue_print(&q);
	enqueue(&q, 30); queue_print(&q);

	item = dequeue(&q); printf("[main] 꺼낸 값 : %d\n", item); queue_print(&q);
	item = dequeue(&q); printf("[main] 꺼낸 값 : %d\n", item); queue_print(&q);
	item = dequeue(&q); printf("[main] 꺼낸 값 : %d\n", item); queue_print(&q);


	return 0;
}