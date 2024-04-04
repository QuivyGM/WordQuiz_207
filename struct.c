#include <stdio.h>

struct student1
{
    char lastName;
    int studentId;
    char grade;
};
typedef struct
{
    char lastName;
    int studentId;
    char grade;
} student2;
int main()
{
    printf("\n2021041069 조형준\n\n");
    struct student1 st1 = {'A', 100, 'A'};         // st1에 값을 집어넣음.
    printf("st1.lastName = %c\n", st1.lastName);   // st1 구조체 안에 있는 lastname의 값을 출력.
    printf("st1.studentId = %d\n", st1.studentId); // st1 구조체 안에 있는 studentId의 값을 출력.
    printf("st1.grade = %c\n", st1.grade);         // st1 구조체 안에 있는 grade의 값을 출력.
    student2 st2 = {'B', 200, 'B'};                // st2에 값을 집어넣음.
    printf("\nst2.lastName = %c\n", st2.lastName); // st2 구조체 안에 있는 lastname의 값을 출력.
    printf("st2.studentId = %d\n", st2.studentId); // st2 구조체 안에 있는 studentId의 값을 출력.
    printf("st2.grade = %c\n", st2.grade);         // st2 구조체 안에 있는 grade의 값을 출력.
    student2 st3;                                  // 새로운 구조체 st3를 선언.
    st3 = st2;                                     // st2의 모든 값을 st3에 대입.
    printf("\nst3.lastName = %c\n", st3.lastName); // st3 구조체 안에 있는 lastname의 값을 출력.
    printf("st3.studentId = %d\n", st3.studentId); // st3 구조체 안에 있는 studentId의 값을 출력.
    printf("st3.grade = %c\n", st3.grade);         // st3 구조체 안에 있는 grade의 값을 출력. 결과적으로 st2값을 대입하였으므로 st2값과 동일.
    /* equality test */
    if (st2.lastName == st3.lastName && st2.studentId == st3.studentId && st2.grade == st3.grade) // 수정한 코드
        // 구조체끼리의 동등성 검사는 불가능. 구조체의 값이 같은지 비교하려면 모든 값을 각각 비교해야 함.
        // Ex) st3=st2 형태로 전체 대입을 하거나 위의 코드처럼 일일이 대입한 값들을 비교.
        printf("\nequal\n");
    else
        printf("\nnot equal\n");
    return 0;
}