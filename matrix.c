#include <stdio.h>
#include <stdlib.h>

void print_matrix(int **matrix, int row, int column)
{
    for (int i = 0; i < row; i++) // 모든 행의 처음부터 끝까지
    {
        for (int j = 0; j < column; j++) // 각 행의 모든 열의 값을 출력
        {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void free_matrix(int **matrix, int row)
{
    for (int i = 0; i < row; i++)
        free(matrix[i]); // 각각의 행들에 대한 메모리 해제
    free(matrix);        // 2차원 배열에 대한 메모리 해제
    // 선언 시에는 2차원 배열 matrix를 할당 후에 각각의 행들에 대해
    // 1차원 배열을 동적으로 할당하였으므로 역순인 1차원, 2차원 순으로 해제.
}

// 덧셈과 뺄셈에서 기본적으로 행과 열이 같음을 전제로 함.
int **addition_matrix(int **A, int **B, int row, int column) // 2차원 배열의 값을 return값으로 받는 함수
{
    int **result = (int **)malloc(sizeof(int *) * row); // A+B의 결과값을 리턴하기 위한 result 2차원 배열의 행 할당.

    for (int i = 0; i < row; i++) // 할당된 각 행에서 각 열들을 추가로 동적 할당하여 2차원 배열을 생성.
        result[i] = (int *)malloc(sizeof(int) * column);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
            result[i][j] = A[i][j] + B[i][j]; // 행렬 덧셈의 정의에 의해 A+B는 각 행과 열에 대응하는 값들을 서로 더하여 결과값이 나옴.
    }
    return result; // 해당 결과값을 반환함.
}

int **subtract_matrix(int **A, int **B, int row, int column) // 2차원 배열의 값을 return값으로 받는 함수
{
    int **result = (int **)malloc(sizeof(int *) * row); // A-B의 결과값을 리턴하기 위한 2차원 배열의 행 할당.

    for (int i = 0; i < row; i++) // 각 행들에 대해 각 열들을 추가로 동적 할당하여 2차원 배열 생성.
        result[i] = (int *)malloc(sizeof(int) * column);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
            result[i][j] = A[i][j] - B[i][j]; // 행렬 뺄셈의 정의에 의해 A-B는 각 행과 열에 대응하는 값들을 서로 빼서 결과값이 나옴.
    }
    return result; // 해당 결과값을 반환함.
}

int **transpose_matrix(int **matrix, int A_row, int A_columm) // 2차원 배열의 값을 return값으로 받는 함수
{
    int **result = (int **)malloc(sizeof(int *) * A_columm); // 전치행렬의 결과값을 리턴하기 위한 2차원 배열의 행 할당.

    for (int i = 0; i < A_columm; i++)
        result[i] = (int *)malloc(sizeof(int) * A_row); // 각 행들에 대해 각 열들을 추가로 동적 할당하여 2차원 배열 생성.

    for (int i = 0; i < A_row; i++)
    {
        for (int j = 0; j < A_columm; j++)
            result[j][i] = matrix[i][j];
        // 전치행렬인 A^T는 A의 행과 열을 서로 바꾼 행렬이므로
        // 정의에 따라 행과 열을 바꿔 result 2차원 배열에 대입해줌.
    }
    return result; // 해당 결과값을 반환함.
}

int **multiply_matrix(int **A, int **B, int A_row, int A_columm, int B_row, int B_columm)
// 행렬 A와 B를 곱하여야 하므로 각 행렬의 size, 즉 행과 열을 모두 인수로 받아야 함.
// 원칙상 A의 열과 B의 행이 동일하지 않으면 곱셈이 불가하나, 위 함수를 포함한 모든 연산은
// A와 B의 행 연산이 가능하다는 것을 전제로 하여 코드를 구성함.
{
    int **result = (int **)malloc(sizeof(int *) * A_row); // A*B의 결과값을 리턴하기 위한 2차원 배열의 행 할당.

    for (int i = 0; i < A_row; i++) // 각 행들에 대해 각 열들을 추가로 동적 할당하여 2차원 배열 생성.
        result[i] = (int *)malloc(sizeof(int) * B_columm);

    // A의 열과 B의 행이 같아야 곱셈이 성립하며
    // 결과로 A의 행과 B의 열만큼의 행렬이 생성됨.
    // Ex) A(2x3) * B(3x2) = C(2x2) Matrix 생성.

    for (int i = 0; i < A_row; i++) // A*B에서 A의 행과 B의 열을 곱하므로 A의 행을 기준으로 반복.
    {
        for (int j = 0; j < B_columm; j++) // 그러므로 B의 열을 기준으로 반복.
        {
            result[i][j] = 0; // res 행렬 초기화
            for (int k = 0; k < B_row /*A_columm*/; k++)
                result[i][j] += A[i][k] * B[k][j];
            // 행과 열은 Fix. 여기서 A의 열과 B의 행만이 변동되므로
            // 변수 k를 통한 반복문으로 덧셈을 제어.
            // result 함수의 1행 1열은 A의 1행과 B의 1열의 각 값들을 곱하여 더한 것이다.
            // 쉽게 말해, A[0][0]=A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0] 이 정의이며
            // 여기서 코드로 구현하기 위해서는 서로의 행과 열이 바뀌어 있을 뿐 서로의 행과 열을 곱하기 때문에
            // A의 열과 B의 행은 동일한 순서로 곱해지며 A의 행과 B의 열은 i, j로 인해 통제되며 이들에 의해 순서가 바뀜.
            // 정리하자면 추가적으로 k라는 변수를 통해 A의 열과 B의 행을 통제함으로서 result값을 도출 가능함.
        }
    }
    return result; // 해당 결과값을 반환함.
}

int main(void)
{
    printf("2021041069 조형준\n");
    int A_row, A_columm, B_row, B_columm;
    printf("행렬 A의 행과 열의 값을 입력하세요: ");
    scanf("%d %d", &A_row, &A_columm);

    printf("\n행렬 B의 행과 열의 값을 입력하세요: ");
    scanf("%d %d", &B_row, &B_columm);

    int **A = (int **)malloc(sizeof(int *) * A_row);

    for (int i = 0; i < A_row; i++)
        A[i] = (int *)malloc(sizeof(int) * A_columm);

    int **B = (int **)malloc(sizeof(int *) * B_row);

    for (int i = 0; i < B_row; i++)
        B[i] = (int *)malloc(sizeof(int) * B_columm);

    // A 행렬과 B 행렬을 각각 사용자가 입력한 값에 따라 동적 할당해줌.

    printf("\n행렬 A의 값\n");
    for (int i = 0; i < A_row; i++)
    {
        for (int j = 0; j < A_columm; j++)
        {
            A[i][j] = rand() % 10 + 1; // rand 함수를 통하여 1~10까지의 랜덤값을 A 행렬에 대입.
            // seed에 따른 변경으로 time.h를 추가하여 srand도 사용 가능하지만 편의상 rand함수를 사용하여 고정된 값을 출력.
        }
    }

    print_matrix(A, A_row, A_columm);

    printf("행렬 B의 값\n");
    for (int i = 0; i < B_row; i++)
    {
        for (int j = 0; j < B_columm; j++)
        {
            B[i][j] = rand() % 10 + 1; // 동일하게 rand 함수를 통하여 1~10까지의 랜덤값을 B 행렬에 대입.
        }
    }

    print_matrix(B, B_row, B_columm);

    int **result_add = addition_matrix(A, B, A_row, A_columm);
    printf("A+B 행렬의 값\n");
    print_matrix(result_add, A_row, A_columm);

    int **result_sub = subtract_matrix(A, B, A_row, A_columm);
    printf("A-B 행렬의 값\n");
    print_matrix(result_sub, A_row, A_columm);

    int **result_transpose = transpose_matrix(A, A_row, A_columm);
    printf("A의 전치행렬의 값\n");
    print_matrix(result_transpose, A_columm, A_row);

    int **result_multiply = multiply_matrix(A, B, A_row, A_columm, B_row, B_columm);
    printf("A*B 행렬의 값\n");
    print_matrix(result_multiply, A_row, B_columm);

    free_matrix(A, A_row);
    free_matrix(B, B_row);

    return 0;
}