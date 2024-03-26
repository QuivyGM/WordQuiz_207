#include <stdio.h>
void print_one(int *ptr, int rows);
int main()
{
    printf("\n2021041069 조형준\n\n");
    int one[] = {0, 1, 2, 3, 4};
    printf("one = %p\n", one);         // 배열의 이름이자 포인터이며 배열의 첫번째 주소인 one[0]의 주소를 가짐.
    printf("&one = %p\n", &one);       // 동일하게 one[0]의 주소값을 출력.
    printf("&one[0] = %p\n", &one[0]); // one[0]의 주소값을 출력. 결과적으로 3개는 같은 값을 가리킴.
    printf("\n");
    printf("------------------------------------\n");
    printf(" print_one(&one[0], 5) \n");
    printf("------------------------------------\n");
    print_one(&one[0], 5); //&one[0]과 5를 인자로 줌.
    printf("------------------------------------\n");
    printf(" print_one(one, 5) \n");
    printf("------------------------------------\n");
    print_one(one, 5); // 위에서 서술했듯 one == &one[0] 이므로 결과적으로 위의 출력값과 동일하게 나옴.
    return 0;
}
void print_one(int *ptr, int rows)
{ /* print out a one-dimensional array using a pointer */
    int i;
    printf("Address \t Contents\n");
    for (i = 0; i < rows; i++)
        printf("%p \t %5d\n", ptr + i, *(ptr + i)); //(ptr + i)의 주소값, 그리고 그 주소값이 참조하는 값을 출력하도록 하는 반복문.
    // 다른 파일들에서 서술했듯 ptr[0]이 시작점이고 선언된 변수의 크기만큼 얼마나 이동할 것인지를 결정함.
    //  Ex) (ptr+1)의 경우 포인터 변수 ptr의 인자가 int형 배열이고 int의 크기는 4byte. 따라서 4byte만큼 1번 이동하므로
    // 결과적으로 &one[1]을 의미하며 *(ptr+1)은 그 참조값을 의미하므로 1이 나옴.
    printf("\n");
}