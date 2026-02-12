#include <stdio.h>
#define MAX 100

typedef struct {
    int id;
    int arrival_time;
    int duration;
    int start_time;
    int finish_time;
} Customer;

int main() {
    int n;
    Customer queue[MAX];
    int total_waiting_time = 0;

    printf("Enter the number of customers: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter arrival time and transaction duration for customer %d: ", i + 1);
        scanf("%d %d", &queue[i].arrival_time, &queue[i].duration);

        queue[i].id = i + 1;

        if(i == 0) {
            // First customer
            queue[i].start_time = queue[i].arrival_time;
        } else {

            if(queue[i-1].finish_time <= queue[i].arrival_time)
                queue[i].start_time = queue[i].arrival_time;
            else
                queue[i].start_time = queue[i-1].finish_time;
        }

        queue[i].finish_time = queue[i].start_time + queue[i].duration;

        total_waiting_time += (queue[i].start_time - queue[i].arrival_time);
    }

    float avg_wait = (float) total_waiting_time / n;

    printf("Average Waiting Time: %.2f\n", avg_wait);

    return 0;
}

