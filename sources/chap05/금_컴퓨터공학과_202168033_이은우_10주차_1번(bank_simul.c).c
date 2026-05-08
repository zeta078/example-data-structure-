/*
프로그램 일시 : 2026.05.08
작성자 : 이은우
작업 제목 : 큐를 활용한 은행 서비스 시뮬레이션 프로그램
원본 코드 : bank_simul.c
기타1 : 10주차 과제 1번 코드
기타2 :	본인의 공부와 이해를 돕기 위한 상세 주석 추가
기타3 : 출력문 수정 및 추가로 시뮬레이션 진행 상황을 더 명확하게 표현
etc : 공백
*/

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

// 프로그램 5.2에서 다음과 같은 부분을 복사한다.
// ================ 원형큐 코드 시작 =================
// 큐의 구조체 정의
// 은행 시뮬레이션에서 고객 정보를 나타냄 : DB로 구현 시 고객 테이블 생성 및 각 고객의 속성 정의
typedef struct {
	int id;              // 고객 ID: 각 고객을 구분하는 고유 번호
	int arrival_time;    // 도착 시간: 고객이 은행에 도착한 시각 (분 단위)
	int service_time;    // 서비스 시간: 고객의 업무 처리에 필요한 시간 (분 단위)
} element;			// 교체!

// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 5 			// 큐의 최대 크기 : 5
typedef struct {
	element  data[MAX_QUEUE_SIZE];  // 큐 데이터를 저장하는 배열
	int  front, rear;               // front: 큐의 앞쪽 인덱스, rear: 큐의 뒤쪽 인덱스
} QueueType;

// 오류 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);		// 강제 종료: 오류 발생 시 프로그램을 종료
}

// 큐 초기화 함수: 큐를 공백 상태로 만듦
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;  // front와 rear를 모두 0으로 초기화하여 빈 큐 상태로 설정
}

// 큐 공백 상태 검출 함수: 큐가 비어있는지 확인
// front = rear -> 큐가 비어있음
int is_empty(QueueType *q)
{
	return (q->front == q->rear);  // front == rear이면 true (1), 아니면 false (0)
}

// 큐 포화 상태 검출 함수: 큐가 가득 찼는지 확인
// 원형 큐에서 rear 다음이 front와 같으면 포화 상태
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 큐 출력 함수: 큐의 현재 상태를 출력
// front와 rear 위치를 표시하고, 큐에 있는 요소들의 도착 시간을 출력
// 출력에 대한 알고리즘이 있음 -> 큐의 요소들을 순회하면서 출력하는 방식
void queue_print(QueueType *q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
			int i = q->front;
			do {
				i = (i + 1) % (MAX_QUEUE_SIZE);
				printf("%d | ", q->data[i].arrival_time);
				if (i == q->rear)
					break;
			} while (i != q->front);
		}
	printf("\n");
}

// 큐 삽입 함수: 큐의 rear에 새로운 요소를 추가
// 포화 상태이면 오류 발생
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");			// 위에서 선언한 오류 함수(void error(char *message)) 호출
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 큐 peek 함수: 검출용 함수
// 공백 상태이면 오류 발생
element peek(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ===== 원형큐 코드 끝 ======

// ===== 메인 함수 시작 ======
int main(void)
{
	int minutes = 15;          // 시뮬레이션 시간 (Ex : 15분, 12분, 60분 등으로 원하는 시간 설정 가능)
	int total_wait = 0;        // 총 대기 시간: 모든 고객의 대기 시간 합계
	int total_customers = 0;   // 총 고객 수: 도착한 고객의 수
	int service_time = 0;      // 현재 서비스 시간: 현재 고객의 남은 서비스 시간
	int service_customer;      // 현재 서비스 중인 고객 ID
	QueueType queue;
	init_queue(&queue);

	srand(time(NULL));         // 난수 생성기 시드 설정: 현재 시간을 시드로 사용
	// 시뮬레이션 루프: 0분부터 minutes에 선언한 시간까지 각 분마다 이벤트 처리

	for (int clock = 0; clock < minutes; clock++) {
		printf("현재시각=%d\n", clock);  // 현재 시각 출력
		// 고객 도착 이벤트: 30% 확률로 고객 도착 (rand()%10 < 3)
		if ((rand()%10) < 3) {
			element customer;  // 새로운 고객 생성
			customer.id = total_customers++;  // 고객 ID 할당 및 총 고객 수 증가
			customer.arrival_time = clock;    // 도착 시간 설정
			customer.service_time = rand() % 3+1;  // 서비스 시간: 1~3분 랜덤
			enqueue(&queue, customer);  // 고객을 큐에 추가
			printf("Entry : 고객 %d이 %d분에 들어옵니다. 업무처리시간= %d분\n", 
				customer.id, customer.arrival_time, customer.service_time);
		}
		// 서비스 처리: 현재 서비스 중인 고객이 있으면 시간 감소
		if (service_time > 0) {
			printf("Progressing : 고객 %d 업무처리중입니다. \n", service_customer);
			service_time--;  // 서비스 시간 1분 감소
			if (service_time == 0) {  // 서비스 시간이 0이 되었으면 업무 완료
				printf("Exit : 고객 %d의 업무가 끝났습니다.\n", service_customer);
			}
		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer = customer.id;
				service_time = customer.service_time;
				printf("Start :고객 %d이 %d분에 업무를 시작합니다. 대기시간은 %d분이었습니다.\n",
					customer.id, clock, clock - customer.arrival_time);
				total_wait += clock - customer.arrival_time;  // 총 대기 시간에 추가
			}
		}
	}
	// 시뮬레이션 종료 후 결과 출력
	printf("전체 대기 시간=%d분 \n", total_wait);
	printf("END : 영업 시간이 종료되었습니다. 다음 시간에 이용해주세요!\n");
	return 0;
}

/*
총 정리 :
해당 코드는 원형 큐를 활용한 은행 서비스 시뮬레이션 예제 프로그램입니다.
고객이 은행에 도착하여 업무를 처리하는 과정을 시뮬레이션하며, 큐를 사용하여 고객의 대기열을 관리합니다.
시뮬레이션 시간 동안 고객이 도착하고, 서비스가 진행되며, 총 대기 시간이 계산되어 출력됩니다.
원형 큐의 특징으로는 front와 rear가 초기에는 q->front = q->rear = 0;  이런 식으로 설정되어 빈 큐 상태를 나타내며,
삽입과 삭제 시 인덱스가 원형으로 돌아가는 방식이 사용된다는 점이다.
*/