#include <stdio.h>
#define MAX_SIZE 100
float sum1(float list[], int);
float sum2(float *list, int);
float sum3(int n, float *list);
float input[MAX_SIZE], answer;
int i;

void main(void)
{
    printf("\n2021041069 조형준\n\n");
    for (i = 0; i < MAX_SIZE; i++)
        input[i] = i; // input[i]에 i값을 대입.

    /* for checking call by reference */
    printf("--------------------------------------\n");
    printf(" sum1(input, MAX_SIZE) \n");
    printf("--------------------------------------\n");
    printf("input \t= %p\n", input);      // input은 배열의 이름이면서 배열의 첫번째인 input[0]의 주소값을 가짐.
    answer = sum1(input, MAX_SIZE);       // sum1 함수의 반환값을 answer변수로 받음.
    printf("The sum is: %f\n\n", answer); // 아래 함수에서 1부터 100까지 모든 배열의 값을 더하라고 했으므로 총합인 4950.000000이 출력.
    printf("--------------------------------------\n");
    printf(" sum2(input, MAX_SIZE) \n");
    printf("--------------------------------------\n");
    printf("input \t= %p\n", input);      // input은 위와 변동사항 없으므로 동일하게 input[0]의 주소값을 가짐.
    answer = sum2(input, MAX_SIZE);       // sum2 함수의 반환값을 answer변수로 받음.
    printf("The sum is: %f\n\n", answer); // 아래 함수에서 1부터 100까지 모든 배열의 값을 더하라고 했으므로 총합인 4950.000000이 출력.
    printf("--------------------------------------\n");
    printf(" sum3(MAX_SIZE, input) \n");
    printf("--------------------------------------\n");
    printf("input \t= %p\n", input);      // 여전히 위와 변동사항 없으므로 동일하게 input[0]의 주소값을 가짐.
    answer = sum3(MAX_SIZE, input);       // sum3 함수의 반환값을 answer변수로 받음.
    printf("The sum is: %f\n\n", answer); // 아래 함수에서 1부터 100까지 모든 배열의 값을 더하라고 했으므로 총합인 4950.000000이 출력.
}

float sum1(float list[], int n) // 인자를 배열과 int형 변수로 받음. (float list[]는 float*list와 동일)
{
    printf("list \t= %p\n", list);     // 위 함수에서 인자를 (input,100)을 받았으므로 받은 인자인 input의 주소값인 input[0]의 주소값을 출력.
    printf("&list \t= %p\n\n", &list); //*** 전역변수로 선언된 배열 input은 sum1 함수에서 지역변수이자 매개변수인 float list[]의 인자가 되고
    // 따라서 &list는 input을 받은 <매개변수 list의 주소값>을 의미한다.
    int i;
    float tempsum = 0;
    for (i = 0; i < n; i++)
        tempsum += list[i];
    return tempsum; // 배열 index 0부터 100까지 모든 배열의 값들을 더하여 반환.
}

float sum2(float *list, int n)
{
    printf("list \t= %p\n", list); // 위 함수에서 인자를 (input,100)을 받았으므로 받은 인자인 input의 주소값인 input[0]의 주소값을 출력.
    // 위에서 서술했듯 매개변수 형태의 float list[]와 float*list는 동일한 형태임. (list[], * 모두 주소값을 받기 때문)
    printf("&list \t= %p\n\n", &list); //*** 전역변수로 선언된 배열 input은 sum1 함수에서 지역변수이자 매개변수인 float *list의 인자가 되고
    // 따라서 &list는 input을 받은 매개변수인 <포인터변수 list의 주소값>을 의미한다.
    int i;
    float tempsum = 0;
    for (i = 0; i < n; i++)
        tempsum += *(list + i); // 앞선 파일들에서 서술했듯 (list+i)는 list의 시작점에서 선언된 변수형태만큼 i번 이동.
    // 다음 반복문의 형태에서는 그러므로 0부터 100까지 첫 인덱스부터 끝 인덱스까지를 모두 더하는 코드이므로 배열값들의 총합이 출력됨.
    return tempsum; // 배열 index 0부터 100까지 모든 배열의 값들을 더하여 반환.
}

/* stack variable reuse test */
float sum3(int n, float *list)
{
    printf("list  \t= %p \n", list);     // 위와 동일하게 input[0]의 주소값을 출력.
    printf("&list  \t= %p \n\n", &list); // 포인터 변수 list의 주소값을 출력.
    // sum1과 sum2에서의 주소값과 차이가 있는 이유는 sum1, sum2 함수의 결과와 대조하여 유추해보았을 때
    // 함수의 매개변수의 순서와 연관이 있겠다는 가정을 얻었고 이 순서에 따라
    // Stack 내의 메모리에서 할당되는 공간이 달라질 수 있겠다는 결론을 내림.
    int i;
    float tempsum = 0;
    for (i = 0; i < n; i++)
        tempsum += *(list + i);
    return tempsum; // sum2와 동일하게 모든 배열의 값들을 더하여 반환.
}