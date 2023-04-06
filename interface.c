#include "interface.h"
#include "scheduler.h"

// Interface implementation
Queue ready;

void init_scheduler(int thread_count)
{
    // TODO: Implement this
    init_queue(&ready);
}

int cpu_me(float current_time, int tid, int remaining_time)
{
    // TODO: Implement this
    pthread_mutex_lock(&lock);
    // Update the global time

    // If the duration is 0, just signal the scheduler that this thread is requesting the CPU
    if (!is_tid_in_queue(&ready, tid))
        enqueue(&ready, tid, current_time);
    // Wait for the CPU to become available for this thread
    while (ready.front->current_task != tid)
    {
        pthread_cond_wait(&cond, &lock);
    }

    // Simulate CPU processing for the specified duration
    if (remaining_time > 0)
    {
        if (current_time > global_time)
        {
            global_time = current_time;
        }
        global_time += 1;
    }
    else
    {
        ready.front->current_task++;
        pthread_cond_broadcast(&cond);
    }
    // Dequeue the current thread from the ready queue
    if (!is_tid_in_queue(&ready, tid))
        dequeue(&ready);

    pthread_mutex_unlock(&lock);

    return global_time;
}

int io_me(float current_time, int tid, int device_id)
{
    // TODO: Implement this
    return 0;
}

void end_me(int tid)
{
    pthread_mutex_lock(&lock);
    if (ready.front->tid == tid)
    {
        ready.front->tid = -1;
        pthread_cond_broadcast(&cond);
    }
    pthread_mutex_unlock(&lock);
}