#include <stdio.h>
#include <stdlib.h>
void main()
{
    printf("\n2021041069 조형준\n\n");
    int **x;
    printf("sizeof(x) = %lu\n", sizeof(x));
    printf("sizeof(*x) = %lu\n", sizeof(*x));
    printf("sizeof(**x) = %lu\n", sizeof(**x));
}

// 예를 들어 int *y; , int z; 를 추가하고 y=&z; , x=&y; 를 추가하면
// y는 z의 주소값, x는 y의 주소값을 가지게 됨.
//*x==y 이고 **x는 z이므로 x와 *x는 주소값, 그리고 **x는 int형 타입의 참조값인 z를 가짐.
// 포인터 변수의 경우 32비트 체제를 기준으로 데이터 타입과 무관하게 4바이트의 사이즈를 가지며
//**x의 경우 참조값인 z가 int형의 변수이므로 4바이트를 출력함.
// 따라서 4 4 4 가 출력.

// 추가하자면 이전 2주차 과제에서도 했었던 내용이지만 32비트 운영체제에서
// 1byte는 8it로 구성되고 따라서 32bit는 4byte이므로 기본 4byte로
// 모든 메모리 주소를 표현 가능하기에 포인터 변수가 4byte를 가짐.
// 64비트 운영체제에서는 8byte이므로 포인터 변수가 8byte를 가지게 되며
// 따라서 64비트 운영체제에서는 8 8 4 가 출력됨.
