#include <stdio.h>
#include <stdlib.h>
void main()
{
    printf("\n\n2021041069 조형준\n\n");
    int list[5];                           // int형 변수를 저장하는 배열 선언
    int *plist[5];                         // 포인터 변수를 저장하는 배열 선언.
    list[0] = 10;                          // list[0]의 값 선언.
    list[1] = 11;                          // list[1]의 값 선언.
    plist[0] = (int *)malloc(sizeof(int)); // 포인터인 plist[0]을 int형 변수의 크기만큼 동적 할당.
    printf("list[0] \t= %d\n", list[0]);   // list[0]의 값인 10을 출력.
    printf("list \t\t= %p\n", list);       // list는 배열의 이름이면서 포인터로도 사용이 가능하며 배열의 첫번째인 list[0]의 주소값을 가지고 있음.
    printf("&list[0] \t= %p\n", &list[0]); // list[0]의 주소값 출력.
    printf("list + 0 \t= %p\n", list + 0); // 변동 없으므로 그대로 list[0]의 주소값을 출력.
    printf("list + 1 \t= %p\n", list + 1); // list는 배열의 맨 앞 주소를 가리킴. 그렇다면 (list+1)은 배열의 시작점부터 선언된 변수형 크기만큼을 이동한다는 의미.
    // 즉, 다시 말해 int형으로 선언된 배열에서 (list+1)은 시작점으로부터 int형의 크기인 4byte만큼을 1번 이동한다는 의미이고 따라서 list[1]의 주소를 출력.
    printf("list + 2 \t= %p\n", list + 2); // 위와 같은 이유로 2번 이동하여 list[2]의 주소값을 출력.
    printf("list + 3 \t= %p\n", list + 3); // 위와 같은 이유로 3번 이동하여 list[3]의 주소값을 출력.
    printf("list + 4 \t= %p\n", list + 4); // 위와 같은 이유로 4번 이동하여 list[4]의 주소값을 출력.
    printf("&list[4] \t= %p\n", &list[4]); // list[4]의 주소값을 출력. 바로 윗줄의 주소값과 동일함을 알 수 있음.

    free(plist[0]);
}