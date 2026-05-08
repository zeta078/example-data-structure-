/*
프로그램 일시 : 2026-03-20
작성자 : 이은우
작업 명칭 : 삼항 연산자와 구조체를 활용한 다항식 계산기(합과 차)
기타 : 3주차 연습 과제 2번
기타2 : 공백
etc : 공백
*/

#include <stdio.h>
#define MAX(a,b) (((a)>(b))?(a):(b)) // 조건에 의한 앞은 참, 뒤는 거짓
#define MAX_DEGREE 101      // 다항식의 최대 차수(다양한 계산을 위한 충분한 크기 지정)
typedef struct { 			// 다항식 구조체 타입 선언
	int degree;			// 다항식의 차수
	float coef[MAX_DEGREE];	// 다항식의 계수
} polynomial;

// 더하기 연산
// C = A+B : 여기서 A와 B는 다항식이다. 구조체가 반환된다. 
polynomial poly_add1(polynomial A, polynomial B) // 더하기 
{
	polynomial C;				// 결과 다항식
	int Apos = 0, Bpos = 0, Cpos = 0;	// 배열 인덱스 변수
	int degree_a = A.degree;            // degree_a는 A의 차수
	int degree_b = B.degree;            // degree_b는 B의 차수
	C.degree = MAX(A.degree, B.degree); // 결과 다항식 차수

    //조건을 비교하기 위한 반복문
	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {  // A항 > B항
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) {  // A항 == B항
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--; degree_b--;
		}
		else {			// B항 > A항
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

// 빼기 연산
// C = A-B : 여기서 A와 B는 다항식이다. 구조체가 반환된다.
polynomial poly_sub1(polynomial A, polynomial B) // 빼기
{
    polynomial C;           // 결과 다항식
    int Apos = 0, Bpos = 0, Cpos = 0;   // 배열 인덱스 변수
    int degree_a = A.degree;            // degree_a는 A의 차수
    int degree_b = B.degree;            // degree_b는 B의 차수
    C.degree = MAX(A.degree, B.degree); // 결과 다항식 차수

    //조건을 비교하기 위한 반복문
    while (Apos <= A.degree && Bpos <= B.degree) {
        if (degree_a > degree_b) {  // A항 > B항
            C.coef[Cpos++] = A.coef[Apos++];
            degree_a--;
        }
        else if (degree_a == degree_b) {  // A항 == B항
            C.coef[Cpos++] = A.coef[Apos++] - B.coef[Bpos++];
            degree_a--; degree_b--;
        }
        else {          // B항 > A항
            C.coef[Cpos++] = -B.coef[Bpos++];
            degree_b--;
        }
    }
    return C;
}

// 다항식 항을 출력하는 함수
void print_poly(polynomial p)
{
	for (int i = p.degree; i>0; i--)
		printf("%3.1fx^%d + ", p.coef[p.degree - i], i);    
	printf("%3.1f \n", p.coef[p.degree]);
}

// 주함수
int main(void)
{
	polynomial a = { 5,{ 3, 6, 0, 0, 0, 10 } }; // 예시로 다항식 A: 3x^5 + 6x^4 + 0x^3 + 0x^2 + 0x + 10 제시 
	polynomial b = { 4,{ 7, 0, 5, 0, 1 } };     // 예시로 다항식 B: 7x^4 + 0x^3 + 5x^2 + 0x + 1 제시    
	polynomial c;                               // 결과 다항식  

    // 출력문
	print_poly(a);
	print_poly(b);
	c = poly_add1(a, b);
	printf("-----------------------------------------------------------------------------\n");
    printf("다항식 A와 B의 합(+) : \n");
	print_poly(c);
	c = poly_sub1(a, b);
	printf("-----------------------------------------------------------------------------\n");
    printf("다항식 A와 B의 차(-) : \n");
	print_poly(c);
	return 0;
}