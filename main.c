#include <stdio.h>
#define MAX 5

int queue[MAX];
int front = -1;
int rear = -1;

void display()
{
    int i;
    if (front == -1)
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue elements: ");
    for (i = front; i <= rear; i++)
    {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

void insert(int value)
{
    if (rear == MAX - 1)
    {
        printf("Queue Overflow\n");
        display();
        return;
    }

    if (front == -1)
        front = 0;

    rear++;
    queue[rear] = value;

    printf("Inserted: %d\n", value);
    display();
}

void delete()
{
    if (front == -1 || front > rear)
    {
        printf("Queue Underflow\n");
        display();
        return;
    }

    printf("Deleted: %d\n", queue[front]);
    front++;

    if (front > rear)
    {
        front = -1;
        rear = -1;
    }

    display();
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n1. Insert\n");
        printf("2. Delete\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(value);
                break;

            case 2:
                delete();
                break;

            case 3:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
