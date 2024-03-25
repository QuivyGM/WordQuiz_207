#include <stdio.h>
#include <stdlib.h>
void main()
{
    printf("\n\n2021041069 조형준\n\n");
    int list[5]; // int형 변수를 저장할 수 있는 배열 공간 생성.
    int *plist[5] = {
        NULL,
    };                                     // 포인터 변수를 저장할 수 있는 배열 공간 생성.
    plist[0] = (int *)malloc(sizeof(int)); // plist[0]에 int 사이즈인 4byte만큼의 공간을 동적으로 할당함.
    list[0] = 1;                           // list[0]의 값을 1로 선언.
    list[1] = 100;                         // list[1]의 값을 100으로 선언.
    *plist[0] = 200;                       // 할당한 곳의 참조값을 200으로 선언.
    printf("list[0] = %d\n", list[0]);     // list[0]의 값인 1을 출력.
    printf("&list[0] = %p\n", &list[0]);   // list[0]의 주소값이 출력.
    printf("list = %p\n", list);           // 배열의 이름, 즉 list는 포인터로도 사용이 가능하며 배열의 맨 앞인 list[0]의 주소값을 가리킴.
    printf("&list = %p\n", &list);         // 앞서 서술했듯이 맨 앞인 list[0]의 주소를 가리키므로 &list는 &list[0], 즉 list[0]의 주소를 출력.
    printf("----------------------------------------\n\n");
    printf("list[1] = %d\n", list[1]);       // list[1]의 값인 100을 출력.
    printf("&list[1] = %p\n", &list[1]);     // list[1]의 주소값을 출력.
    printf("*(list+1) = %d\n", *(list + 1)); // list는 배열의 맨 앞 주소를 가리킴. 그렇다면 (list+1)은 배열의 시작점부터 선언된 변수형 크기만큼을 이동한다는 의미.
    // 즉, 다시 말해 int형으로 선언된 배열에서 (list+1)은 시작점으로부터 int형의 크기인 4byte만큼을 1번 이동한다는 의미이고 따라서 list[1]의 주소를 의미함.
    // 따라서 *(list+1)은 주소의 참조값을 출력하므로 list[1]의 값인 100을 출력.
    printf("list+1 = %p\n", list + 1); // 바로 위에서 서술한 결과로 (list+1)은 list[1]의 주소값을 출력.
    printf("----------------------------------------\n\n");
    printf("*plist[0] = %d\n", *plist[0]); // plist[0]이 참조하는 값인 200을 출력.
    printf("&plist[0] = %p\n", &plist[0]); // 포인터 배열 plist[0]의 주소를 출력.
    printf("&plist = %p\n", &plist);       // 앞서 서술했듯 plist는 해당 배열의 첫번째인 plist[0]의 주소값을 가리키고 있으므로 plist[0]의 주소 출력.
    printf("plist = %p\n", plist);         // 위와 동일하게 plist 또한 해당 배열의 첫 번째 주소인 plist[0]의 주소와 동일.
    printf("plist[0] = %p\n", plist[0]);   // plist[0]은 참조값 200의 주소값을 가지고 있는 포인터이고 그 주소값을 출력.
    printf("plist[1] = %p\n", plist[1]);   // 위에서 NULL값으로 선언하였으므로 NULL값 출력.
    printf("plist[2] = %p\n", plist[2]);   // 위에서 NULL값으로 선언하였으므로 NULL값 출력.
    printf("plist[3] = %p\n", plist[3]);   // 위에서 NULL값으로 선언하였으므로 NULL값 출력.
    printf("plist[4] = %p\n", plist[4]);   // 위에서 NULL값으로 선언하였으므로 NULL값 출력.
    free(plist[0]);                        // 동적할당해준 plist[0] 사용을 해제시켜줌.
}