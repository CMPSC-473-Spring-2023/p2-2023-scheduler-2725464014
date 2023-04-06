
#include "scheduler.h"

// TODO: Add your function definitions here.
Queue ready_queue;

void init_queue(Queue *q)
{
    q->front = NULL;
    q->rear = NULL;
}

bool is_queue_empty(Queue *q)
{
    return q->front == NULL;
}

void enqueue(Queue *q, int tid, float arrival_time)
{
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
    temp->tid = tid;
    temp->arrival_time = arrival_time;

    temp->next = NULL;

    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

int dequeue(Queue *q)
{
    if (is_queue_empty(q))
    {
        return -1;
    }

    QueueNode *temp = q->front;
    int tid = temp->tid + 1;

    q->front = temp->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp);

    return tid;
}
int get_shortest_remaining_tid(Queue *queue)
{
    if (queue->front == NULL)
    {
        return -1;
    }

    struct QueueNode *temp = queue->front;
    float min_arrival_time = temp->arrival_time;
    int min_remaining_time = temp->remaining_time;
    int min_tid = temp->tid;

    while (temp != NULL)
    {
        if (temp->remaining_time < min_remaining_time)
        {
            min_arrival_time = temp->arrival_time;
            min_tid = temp->tid;
            min_remaining_time = temp->remaining_time;
        }
        temp = temp->next;
    }

    return min_tid;
}
bool is_tid_in_queue(Queue *queue, int tid)
{
    if (queue == NULL)
    {
        return false;
    }

    struct QueueNode *temp = queue->front;
    while (temp != NULL)
    {
        if (temp->tid == tid)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
