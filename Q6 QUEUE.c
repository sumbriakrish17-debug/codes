#include <stdio.h>
#include <stdlib.h>

#define TELLERS 4
#define MAX 100

typedef struct
{
    int id;
    int arrival_time;
    int duration;
    int start_time;
    int finish_time;
} Customer;

typedef struct
{
    Customer data[MAX];
    int front;
    int rear;
} Queue;

Queue queues[TELLERS];
int teller_available[TELLERS];

void initQueues()
{
    for (int i = 0; i < TELLERS; i++)
    {
        queues[i].front = -1;
        queues[i].rear = -1;
        teller_available[i] = 0;
    }
}

int isEmpty(Queue *q)
{
    return (q->front == -1);
}

void enqueue(Queue *q, Customer c)
{
    if (q->rear == MAX - 1)
        return;

    if (q->front == -1)
        q->front = 0;

    q->rear++;
    q->data[q->rear] = c;
}

Customer dequeue(Queue *q)
{
    Customer c = q->data[q->front];

    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;

    return c;
}

void displayQueues()
{
    for (int i = 0; i < TELLERS; i++)
    {
        printf("Queue %d: ", i + 1);

        if (queues[i].front == -1)
        {
            printf("Empty");
        }
        else
        {
            for (int j = queues[i].front; j <= queues[i].rear; j++)
                printf("[C%d T%d] ", queues[i].data[j].id, queues[i].data[j].duration);
        }

        printf("\n");
    }
    printf("\n");
}

int getShortestQueue()
{
    int min = 9999;
    int index = 0;

    for (int i = 0; i < TELLERS; i++)
    {
        int length;
        if (queues[i].front == -1)
            length = 0;
        else
            length = queues[i].rear - queues[i].front + 1;

        if (length < min)
        {
            min = length;
            index = i;
        }
    }

    return index;
}

int main()
{
    int num_customers;
    int trans_duration[4];
    int total_waiting_time = 0;

    printf("Enter number of customers: ");
    scanf("%d", &num_customers);

    printf("Enter duration of 4 transaction types:\n");
    for (int i = 0; i < 4; i++)
        scanf("%d", &trans_duration[i]);

    initQueues();

    for (int i = 0; i < num_customers; i++)
    {
        Customer c;
        int type;

        printf("Customer %d arrival time: ", i + 1);
        scanf("%d", &c.arrival_time);

        printf("Transaction type (1-4): ");
        scanf("%d", &type);

        c.id = i + 1;
        c.duration = trans_duration[type - 1];

        int teller = getShortestQueue();

        if (teller_available[teller] <= c.arrival_time)
            c.start_time = c.arrival_time;
        else
            c.start_time = teller_available[teller];

        c.finish_time = c.start_time + c.duration;
        teller_available[teller] = c.finish_time;

        total_waiting_time += (c.start_time - c.arrival_time);

        enqueue(&queues[teller], c);

        printf("\nAfter Customer %d arrival:\n", c.id);
        displayQueues();
    }

    float avg_wait = (float)total_waiting_time / num_customers;

    printf("Average Waiting Time: %.2f\n", avg_wait);

    return 0;
}
