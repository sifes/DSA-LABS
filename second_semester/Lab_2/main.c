#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    float data;
    struct Node* next;
} Node; // лінійний однозв'язний список

// Функція для створення нового вузла
Node* createNode(float data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Функція для вставки нового вузла у початок списку
Node* insertNode(Node* currentNode, float data) {
    if (!currentNode) {
        currentNode = createNode(data);
    } else {
        Node* newNode = createNode(data);
        newNode->next = currentNode;
        currentNode = newNode;
    }
    return currentNode;
}

// Функція для виведення списку на екран
void printList(Node* currentNode) {
    Node* pointer = currentNode;
    while (pointer) {
        printf("%f ", pointer->data);
        pointer = pointer->next;
    }
    printf("\n");
}

// Функція для вивільнення пам'яті, звільнення списку
void freeList(Node* currentNode) {
    Node* temp = NULL;
    while (currentNode != NULL) {
        temp = currentNode;
        currentNode = currentNode->next;
        free(temp);
    }
}

// Функція для перестановки вузлів у списку
void swapList(Node** headRef) {
    Node* head = *headRef;
    if (!head || !head->next)
        return;

    // знайти середину листа
    Node* slow = head;
    Node* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // відокремити листи на 2 частини
    Node* secondHalf = slow->next;
    slow->next = NULL;

    Node* currentOfSecondHalf = secondHalf;
    Node* nextNode = currentOfSecondHalf->next;
    currentOfSecondHalf->next = NULL;
    while (nextNode) {
        currentOfSecondHalf = insertNode(currentOfSecondHalf, nextNode->data);
        nextNode = nextNode->next;
    }

    // об'єднати два листа в один
    Node* currentOfFirstHalf = head;
    while (currentOfSecondHalf) {
        // зберігаємо наступні елементи кожної половини
       Node* nextOfFirstHalf = currentOfFirstHalf->next;
       Node* nextOfSecondHalf = currentOfSecondHalf->next;
        // об'єднуємо листи
       currentOfFirstHalf->next = currentOfSecondHalf;
       currentOfSecondHalf->next = nextOfFirstHalf;
        // переходимо до наступних елементів
       currentOfSecondHalf = nextOfSecondHalf;
       currentOfFirstHalf = nextOfFirstHalf;
   }
}

int main() {
    float data;
    Node* head = NULL;
    int n;
    printf("enter n =");
    scanf("%d", &n);
    // Зчитуємо дані для створення списку з консолі
    printf("Enter the values for the nodes\n");
    for (int i = 0; i < n; i++) {
        printf("Enter a value:");
        scanf("%f", &data);
        head = insertNode(head, data);
    }
    // Виводимо початковий список на екран
    printf("Original list: ");
    printList(head);

    // Переставляємо вузли у списку
    swapList(&head);

    // Виводимо переставлений список на екран
    printf("Rearranged list: ");
    printList(head);

    // Звільняємо пам'ять, вивільняємо список
    freeList(head);

    return 0;
}
