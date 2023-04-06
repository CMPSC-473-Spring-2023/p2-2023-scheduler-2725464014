/*
 * Utilize "scheduler.h" and "scheduler.c" for all the utility functions students
 * intend to use for "interface.c".
 */
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <pthread.h>

#include "interface.h"

typedef struct QueueNode
{
    int tid;
    float arrival_time;
    int current_task;
    int remaining_time;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

void init_queue(Queue *q);
bool is_queue_empty(Queue *q);
void enqueue(Queue *q, int tid, float arrival_time);
int dequeue(Queue *q);
int get_shortest_remaining_tid(Queue *queue);
bool is_tid_in_queue(Queue *queue, int tid);

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static float global_time;

#endif