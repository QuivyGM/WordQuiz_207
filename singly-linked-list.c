/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science
 *  at Chungbuk National University
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node
{
    int key;
    struct Node *link;
} listNode;

typedef struct Head
{
    struct Node *first;
} headNode;

/* 함수 리스트 */
headNode *initialize(headNode *h);
int freeList(headNode *h);

int insertFirst(headNode *h, int key); // 머리에 집어넣기
int insertNode(headNode *h, int key);  // 비어있지 않은 상태에서 사이에 끼워넣기
int insertLast(headNode *h, int key);  // 마지막 부분에 연결하기

int deleteFirst(headNode *h);         // head가 가리키는 노드 삭제
int deleteNode(headNode *h, int key); // 중간에 낀 노드 삭제
int deleteLast(headNode *h);          // 마지막 노드 삭제
int invertList(headNode *h);          // 리스트 순서 뒤집기

void printList(headNode *h); // 전체 결과값 출력

int main()
{
    printf("\n2021041069 조형준\n");
    char command;
    int key;
    headNode *headnode = NULL;

    /*while문을 쓸 경우 입력받은 후에 진입하면서
    걸리기 때문에 실행문을 들어가지 못하게 됨.*/
    // do while문을 쓸 경우 while문이 마지막에서 걸리므로
    // 최소 1번의 초기 실행을 보장함.

    do
    {
        printf("----------------------------------------------------------------\n");
        printf("                     Singly Linked List                         \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'z':
        case 'Z':
            headnode = initialize(headnode);
            break;
        case 'p':
        case 'P':
            printList(headnode);
            break;
        case 'i':
        case 'I':
            printf("Your Key = ");
            scanf("%d", &key);
            insertNode(headnode, key);
            break;
        case 'd':
        case 'D':
            printf("Your Key = ");
            scanf("%d", &key);
            deleteNode(headnode, key);
            break;
        case 'n':
        case 'N':
            printf("Your Key = ");
            scanf("%d", &key);
            insertLast(headnode, key);
            break;
        case 'e':
        case 'E':
            deleteLast(headnode);
            break;
        case 'f':
        case 'F':
            printf("Your Key = ");
            scanf("%d", &key);
            insertFirst(headnode, key);
            break;
        case 't':
        case 'T':
            deleteFirst(headnode);
            break;
        case 'r':
        case 'R':
            invertList(headnode);
            break;
        case 'q':
        case 'Q':
            freeList(headnode);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

headNode *initialize(headNode *h)
{

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if (h != NULL)
        freeList(h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    headNode *temp = (headNode *)malloc(sizeof(headNode));
    temp->first = NULL;
    return temp;
    // h를 해제시켰으므로 추가적으로 malloc을 통한 메모리 할당으로
    // 함수의 return값을 반환해줌.
}

int freeList(headNode *h)
{
    /* h와 연결된 listNode 메모리 해제
     * headNode도 해제되어야 함.
     */
    listNode *p = h->first; // 임의의 포인터 p를 head를 가리키게 함.

    listNode *prev = NULL; // p의 선행 노드는 없으므로 NULL값을 가짐.
    while (p != NULL)
    {
        prev = p;    // 이전 값을 prev에 주고
        p = p->link; // p가 하나씩 건너가면서
        free(prev);  // prev값을 모두 해제시켜준다.
    }
    free(h); // 작업이 모두 끝나면 head도 메모리 해제.
    return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
// 앞쪽에 하나 추가.
int insertFirst(headNode *h, int key)
{
    // 머리에 초기 리스트 head값을 넣어주기.
    listNode *node = (listNode *)malloc(sizeof(listNode)); // 추가할 노드 생성.
    node->key = key;                                       // 매개변수 key값을 노드의 key값에 대입.

    node->link = h->first; // node의 next 포인터가 head->first가 가리키는 기존 head값을 가리킴.
    h->first = node;       // head가 가리키는 값을 추가된 노드로 옮겨줌.

    return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
// 여기 Case 나누는 게 진짜 어려웠어요........ㅠㅠ
int insertNode(headNode *h, int key)
{ // listNode : int key, *link

    // first 노드보다 큰 경우, 작은 경우 2가지 Case
    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key;
    node->link = NULL;
    listNode *p = h->first;

    // Case 1 : head가 비었거나 head보다 값이 작다면
    if (h->first == NULL || key < p->key)
    { // head에 추가하고 head는 추가된 새로운 노드를 가리키게 함.
        insertFirst(h, key);
        return;
    }

    // Case 2 : 중간에 낑기기
    while (p->link != NULL && p->link->key < key) // 마지막 노드, 또는 중간에 낑기는 경우에서 탈출.
        p = p->link;

    // 다시 마지막 노드까지 온 경우, 중간에 낑기는 경우로 Case 분할.

    // Case 2-1 : 중간에 낑기는 경우 (p->link, 즉 p의 다음값보다는 key값이 작은 경우)
    node->link = p->link; //
    p->link = node;
    // node를 먼저 엮는 이유는 p의 link를먼저 엮게 되면
    // 이전 p->link값이 소실됨.

    // Case 2-2 : 마지막 노드인 경우
    if (p->link == NULL)
    {
        insertLast(h, key); // 마지막에 삽입.
        return;
    }

    return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode *h, int key)
{
    // 마지막 노드에서의 비교
    // 마찬가지로 마지막 노드보다 클 경우, 작을 경우 2 Case.
    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key;
    node->link = NULL;

    listNode *p = h->first;
    while (p->link != NULL) // 마지막 노드까지 이동.
        p = p->link;        // p값이 마지막 노드일 때까지 계속 건너감.

    p->link = node; // 마지막 노드 바로 뒤에 연결.
    return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode *h)
{
    listNode *p = h->first; // 포인터 p가 head노드를 가리키도록 설정.
    if (p == NULL)
        return;

    h->first = p->link; // head가 가리키는 곳을 head->next로 옮겨줌.
    free(p);            // 그리고 p가 가리키는 head first를 메모리 해제.
    return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode *h, int key)
{
    listNode *p = h->first; // 현재 가리키는 노드는 first노드
    listNode *prev = NULL;

    // Case 1 : head에 있는 노드를 삭제하는 경우
    // 비어있지 않으면서 first의 key가 key와 일치한다면
    if (h->first != NULL && h->first->key == key)
    {
        deleteFirst(h);
        return;
    }

    // Case 2 : Head 뒤에 있는 노드를 삭제하는 경우

    while (p != NULL && p->key != key) // 마지막 노드까지 전부 비교했거나 그 전에 key값을 찾은 경우 탈출.
    {
        prev = p;
        p = p->link;
    }

    // Case 2-1 : 중간에 낑긴 노드를 삭제하는 경우
    prev->link = p->link;
    free(p);

    // Case 2-2 : 마지막 노드이면서 key값과 일치하는 경우
    if (p->key == NULL)
    {
        deleteLast(h);
        return;
    }

    // Case 2-3 : 끝까지 돌았는데도 key 값이 존재하지 않으면
    if (p == NULL)
        return;

    return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode *h)
{
    listNode *p = h->first;
    listNode *prev = NULL;
    while (p->link != NULL) // p가 마지막 노드를 가리키면 탈출.
    {
        prev = p;
        p = p->link; // p값이 마지막 노드일 때까지 계속 건너감.
    }
    prev->link = NULL; // p인 마지막 노드까지 메모리 해제.
    free(p);           // 마지막 노드를 가리키는 p 포인터를 해제시켜줌.
    return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode *h) // 3개의 포인터를 이용한 역순 Cycle 만들기.
{
    // 이전값, 현재값, 다음값을 받아주는 3개의 포인터를 사용.
    // Why? 계속해서 연속된 값들을 받아줘야 1개의 역순 Cycle을 만들 수 있음.
    listNode *prev = NULL;
    listNode *p = h->first;
    listNode *next = NULL;

    while (p != NULL)
    {
        next = p->link;
        p->link = prev;
        // 여기까지 1 Cycle

        prev = p;
        p = next;
        // prev, p를 한칸씩 땡겨줌.
    }
    // p가 NULL이 되면서 탈출함으로서 노드의 마지막인
    // prev 값까지 모두 역순으로 정렬이 된 상태.
    // 따라서 노드의 마지막인 prev값을 head가 가리키게 함.
    h->first = prev;
    return 0;
}

void printList(headNode *h)
{
    int i = 0;
    listNode *p = h->first;

    printf("\n---PRINT\n");

    if (h == NULL)
    {
        printf("Nothing to print....\n");
        return;
    }

    while (p != NULL)
    {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->link;
        i++;
    }

    printf("  items = %d\n", i);
}