#include <stdio.h>
struct student
{
    char lastName[13]; /* 13 bytes */ // 13바이트이므로 가까운 4의 배수인 16을 채우기 위해 padding byte가 3byte 추가로 들어감.
    int studentId; /* 4 bytes */      // 이미 4의 배수이므로 padding byte X.
    short grade; /* 2 bytes */        // 가장 가까운 4의 배수인 4를 채우기 위해 padding byte가 2byte 추가로 들어감.
    // 따라서 원래 크기 19byte에 padding byte가 5byte 추가로 들어가므로 총 24byte의 크기가 됨.
};
int main()
{
    printf("\n2021041069 조형준\n\n");
    struct student pst;
    printf("size of student = %ld\n", sizeof(struct student)); // 위 설명에 의하여 구조체의 크기는 24byte.
    printf("size of int = %ld\n", sizeof(int));                // int 자료형의 크기는 4byte.
    printf("size of short = %ld\n", sizeof(short));            // short 자료형의 크기는 2byte.
    return 0;
}