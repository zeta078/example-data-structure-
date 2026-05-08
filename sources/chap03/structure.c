#include <stdio.h>

typedef struct studentTag {
	int hackbun; //학번 ex) 20230001
	char gender[10]; //성별 ex) "남자", "여자"
	char name[10]; // 조회할려는 학생의 이름
	int age;	  // 조회할려는 학생의 나이
	double gpa;	  // 조회할려는 학생의 평균평점

} student;

int main(void)
{
	student a = {  202168033, "남자", "kim", 20, 4.3 };
	student b = {  202168034, "여자", "park", 21, 4.2 };

	printf("==========================================\n");
	printf("학번 : %d, 성별 : %s, 이름 : %s, 나이 : %d, 평균평점 : %.2f \n", a.hackbun, a.gender, a.name, a.age, a.gpa);
	printf("학번 : %d, 성별 : %s, 이름 : %s, 나이 : %d, 평균평점 : %.2f \n", b.hackbun, b.gender, b.name, b.age, b.gpa);
	printf("==========================================\n");

	return 0;
}