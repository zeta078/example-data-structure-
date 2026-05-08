/*
프로그램 일시 : 2026-03-20
작성자 : 이은우
작업 명칭 : 구조체를 활용한 학생 정보 출력 프로그램
기타 : 3주차 연습 과제 1번
기타2 : 공백
etc : 공백
*/

#include <stdio.h>

typedef struct studentTag {
	int hackbun; //학번 ex) 20230001
	char gender[10]; //성별 ex) "남자", "여자"
	char name[10]; // 조회할려는 학생의 이름
	int age;	  // 조회할려는 학생의 나이
	double gpa;	  // 조회할려는 학생의 평균평점

} student;

//메인함수
int main(void)
{
    //출력할려고 하는 학생의 학번, 성별, 이름, 나이, 평균평점 순서로 나열
	student a = {  202168033, "남자", "kim", 20, 4.3 };
	student b = {  202168034, "여자", "park", 21, 4.2 };

    //구조체에 있는 학생의 정보를 출력하는 printf문
	printf("==========================================\n");
	printf("학번 : %d, 성별 : %s, 이름 : %s, 나이 : %d, 평균평점 : %.2f \n", a.hackbun, a.gender, a.name, a.age, a.gpa);
	printf("학번 : %d, 성별 : %s, 이름 : %s, 나이 : %d, 평균평점 : %.2f \n", b.hackbun, b.gender, b.name, b.age, b.gpa);
	printf("==========================================\n");

	return 0;
}