#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COUNT 10

#define MAX2(x, y) ((x) > (y) ? (x) : (y))
#define MAX(x, y, z) (MAX2(x, y) > (z) ? MAX2(x, y) : (z))
#define MIN2(x, y) ((x) < (y) ? (x) : (y))
#define MIN(x, y, z) (MIN2(x, y) < (z) ? MIN2(x, y) : (z))
#define SWAP(x, y) ( (x) ^= (y); (y) ^= (x); (x) ^= (y); )
#define SETBIT(mask, bit) (mask |=  (1 << bit))
#define CLEARBIT(mask, bit) (mask &= ~(1 << bit))
#define INVERSEBIT(mask, bit) (mask ^=  (1 << bit))
#define CHECKBIT(mask, bit) (mask & (1 << bit) == 1 ? (1) : (0))

typedef struct Book
{
    char title[150];
    char author[100];
    int pages;
    double price;
} Book;

typedef struct NodeBook
{
    Book value; 
    struct NodeBook* next;
} NodeBook;

typedef struct LinkedListBook
{
    struct NodeBook* head;
    struct NodeBook* tail; 
    int size; 
} LinkedListBook; 

typedef struct Node
{
    int value;
    struct Node* next; 
    struct Node* prev;
} Node;

typedef struct Deque
{
    struct Node* head;
    struct Node* tail; 
} Deque; 

//helper
char randomChar()
{
    int token = rand() % (10 - (-10) + 1) + (-10);

    if (token > 0)
    {
        return rand() % (90 - 65 + 1) + 65;
    }
    else
    {
        return rand() % (122 - 97 + 1) + 97;
    }
    
    return 'a';
}

//helper
char* randomCharArray()
{
    int length = rand() % (20 - 10 + 1) + 10;
    int size = 0;
    char str[20] = "";

    while (size < length)
    {
        char c[2];
        c[1] = '\0';
        c[0] = randomChar();
        
        strcat(str, c);
        ++size; 
    }

    char* str2 = &str[0];

    return str2;
}

Deque* createDeque()
{
    Deque* deque = (Deque*)malloc(sizeof(Deque));

    if (!deque)
    {
        exit(-1); 
    }

    deque->head = NULL;
    deque->tail = NULL;

    return deque; 
}

int isEmpty(Deque* deque)
{
    if (deque->head == NULL && deque->tail == NULL)
    {
        return 1;
    }

    return 0; 
}

void push_back_Deque(Deque* deque, int element)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->value = element;
    temp->next = NULL;
    temp->prev = NULL;

    if (isEmpty(deque) == 1)
    {
        deque->head = temp;
        deque->tail = deque->head;
        return; 
    }

    temp->prev = deque->tail;
    deque->tail->next = temp; 
    deque->tail = temp;
}

void push_front_Deque(Deque* deque, int element)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->value = element;
    temp->prev = NULL;
    temp->next = NULL;

    if (isEmpty(deque) == 1)
    {
        deque->head = temp;
        deque->tail = deque->head;
        return; 
    }

    temp->next = deque->head;
    deque->head->prev = temp; 
    deque->head = temp;
}

void pop_front_Deque(Deque* deque)
{
    if (isEmpty(deque) == 1)
    {
        printf("Empty...\n");
        return;
    }
    else if (deque->head == deque->tail)
    {
        free(deque->head);
        deque->head = NULL;
        deque->tail = NULL; 
        return; 
    }

    Node* temp = deque->head;
    deque->head = deque->head->next;
    deque->head->prev = NULL;
    free(temp);
}

void pop_back_Deque(Deque* deque)
{
    if (isEmpty(deque) == 1)
    {
        printf("Empty...\n");
        return;
    }
    else if (deque->head == deque->tail)
    {
        free(deque->head);
        deque->head = NULL;
        deque->tail = NULL; 
        return; 
    }

    Node* temp = deque->tail;
    deque->tail = deque->tail->prev;
    deque->tail->next = NULL;
    free(temp);
}

void freeDeque(Deque* deque)
{
    // Node* current = deque->head;

    // while (current != NULL)
    // {
    //     Node* temp = current;
    //     current = current->next;
    //     free(temp); 
    // }

    // deque->head = NULL;
    // deque->tail = NULL;

    while(deque->head != NULL)
    {
        pop_front_Deque(deque);
    }

    free(deque);
    printf("Deque was freed...\n");
}

int peek_head_Deque(Deque* deque)
{
    return deque->head->value;
}

int peek_tail_Deque(Deque* deque)
{
    return deque->tail->value;
}

void printDeque(Deque* deque)
{
    Node* current = deque->head;
    printf("Deque: ");

    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    
    printf("\n");
}

LinkedListBook* createLinkedListBook()
{
    LinkedListBook* books = (LinkedListBook*)malloc(sizeof(NodeBook));

    if (!books)
    {
        exit(-1);
    }

    books->head = NULL;
    books->tail = NULL;
    books->size = 0; 

    return books; 
}

void fillNodeBook(NodeBook* book)
{
    book->value.pages = rand() % (2000 - 5 + 1) + 5;
    book->value.price = rand() % (1000 - 1 + 1) + 1.0;
    strcpy(book->value.author, randomCharArray()); 
    strcpy(book->value.title, randomCharArray()); 
    book->next = NULL; 
}

int isEmptyLinkedList(LinkedListBook* books)
{
    if (books->head == NULL && books->tail == NULL && books->size == 0)
    {
        return 1;
    }

    return 0; 
}

void push_back_LinkedList(LinkedListBook* books)
{
    if (books->size == COUNT)
    {
        printf("FULL\n");
        return; 
    }
    
    NodeBook* temp = (NodeBook*)malloc(sizeof(NodeBook));
    fillNodeBook(temp); 

    if (isEmptyLinkedList(books) == 1)
    {
        books->head = temp;
        books->tail = books->head;
        books->size = 1; 
        return; 
    }

    books->tail->next = temp; 
    books->tail = temp;
    books->size += 1; 
}

void pop_front_LinkedList(LinkedListBook* books)
{
    if (isEmptyLinkedList(books) == 1)
    {
        printf("Empty...\n");
        return;
    }
    else if (books->head == books->tail)
    {
        free(books->head);
        books->head = NULL;
        books->tail = NULL; 
        books->size = 0; 
        return; 
    }

    NodeBook* temp = books->head;
    books->head = books->head->next;
    free(temp);
    books->size -= 1; 
}

void freeLinkedList(LinkedListBook* books)
{
    while(books->head != NULL)
    {
        pop_front_LinkedList(books);
    }

    free(books);
    printf("LinkedList was freed...\n");
}

char* peek_head_LinkedList(LinkedListBook* books)
{
    return books->head->value.title;
}

char* peek_tail_LinkedList(LinkedListBook* books)
{
    return books->tail->value.title;
}

int size_LinkedList(LinkedListBook* books)
{
    return books->size; 
}

void printLinkedList(LinkedListBook* books)
{
    NodeBook* current = books->head;
    printf("LinkedList:\n");

    while (current != NULL)
    {
        printf("TITLE: %25s, AUTHOR: %25s, PAGES: %5d, PRICE: %5.2lf\n", current->value.title, current->value.author, current->value.pages, current->value.price);
        current = current->next;
    }
    
    printf("\n");
}

void swap(NodeBook* a, NodeBook* b) 
{ 
    Book temp = a->value; 
    a->value = b->value; 
    b->value = temp; 
} 

void bubbleSort(LinkedListBook* books) 
{ 
    if (books->head == NULL) 
    {
        printf("Empty...\n");
        return;
    }

    int swapped; 
    NodeBook* current; 
    NodeBook* tempLast = NULL; 
  
    do
    { 
        swapped = 0; 
        current = books->head; 
  
        while (current->next != tempLast) 
        {  
            if (strcmp(current->value.title, current->next->value.title) > 0)
            { 
                swap(current, current->next); 
                swapped = 1; 
            } 

            current = current->next; 
        } 

        tempLast = current; 
    } 
    while (swapped); 
} 

void task1()
{
    Deque* deque = createDeque();

    printf("IsEmpty: %d\n", isEmpty(deque));

    printf("Push back:\n");
    push_back_Deque(deque, 1);
    printf("Head: %d, Tail: %d\n", peek_head_Deque(deque), peek_tail_Deque(deque));
    printDeque(deque);
    push_back_Deque(deque, 2);
    printf("Head: %d, Tail: %d\n", peek_head_Deque(deque), peek_tail_Deque(deque));
    printDeque(deque);
    push_back_Deque(deque, 3);
    printf("Head: %d, Tail: %d\n", peek_head_Deque(deque), peek_tail_Deque(deque));
    printDeque(deque);
    push_back_Deque(deque, 4);
    printf("Head: %d, Tail: %d\n", peek_head_Deque(deque), peek_tail_Deque(deque));
    printDeque(deque);

    printf("Pop back:\n");
    pop_back_Deque(deque);
    printf("Head: %d, Tail: %d\n", peek_head_Deque(deque), peek_tail_Deque(deque));
    printDeque(deque);

    printf("Push front:\n");
    push_front_Deque(deque, 5);
    printf("Head: %d, Tail: %d\n", peek_head_Deque(deque), peek_tail_Deque(deque));
    printDeque(deque);

    printf("Pop front:\n");
    pop_front_Deque(deque);
    printf("Head: %d, Tail: %d\n", peek_head_Deque(deque), peek_tail_Deque(deque));
    printDeque(deque);

    printf("Pop front:\n");
    pop_front_Deque(deque);
    printf("Head: %d, Tail: %d\n", peek_head_Deque(deque), peek_tail_Deque(deque));
    printDeque(deque);

    printf("Pop front:\n");
    pop_front_Deque(deque);
    printf("Head: %d, Tail: %d\n", peek_head_Deque(deque), peek_tail_Deque(deque));
    printDeque(deque); 

    freeDeque(deque);
}

void task2()
{
    srand(time(0));
    int size = 0;

    LinkedListBook* books = createLinkedListBook();

    while (size < COUNT)
    {
        push_back_LinkedList(books);
        ++size; 
    }
    
    printLinkedList(books);
    bubbleSort(books);
    printLinkedList(books);

    freeLinkedList(books);
}

void task3()
{
    printf("%d\n", MAX(4, 3, 5));
    printf("%d\n", MIN(4, 3, 5));

    int a = 1; int b = 2;
    //SWAP(a, b);
    printf("%d, %d\n", a, b);

    int mask = 11; 
    SETBIT(mask, 2);
    printf("%d\n", mask);
    CLEARBIT(mask, 2);
    printf("%d\n", mask);
    INVERSEBIT(mask, 2);
    printf("%d\n", mask);
    INVERSEBIT(mask, 3);
    printf("%d\n", mask);
    printf("%d", CHECKBIT(mask, 3));

}

int main()
{
    //task1();
    //task2();
    task3();
    
    return 0; 
}