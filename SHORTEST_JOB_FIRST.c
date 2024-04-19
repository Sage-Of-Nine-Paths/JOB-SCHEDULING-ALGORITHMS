#include "IMP_FUNCTIONS.h"
#include <time.h>

int compare(int a, int b)
{
    if (p[a].IO_call < p[b].IO_call)
        return 1;
    else
        return 0;
}

void min_heapify(int i)
{
    int heap_size = rq.size - 1;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left <= heap_size && compare(rq.process_id[left], rq.process_id[largest]))
        largest = left;

    if (right <= heap_size && compare(rq.process_id[right], rq.process_id[largest]))
        largest = right;

    if (largest != i)
    {
        swap(&rq.process_id[largest], &rq.process_id[i]);
        min_heapify(largest);
    }
}

void add_rq(int x, int time)
{
    int i = rq.size++;
    rq.process_id[i] = x;
    p[x].rq_arrival_time = time;
    printf("Process %d entered into ready queue at time %d.\n", x, p[x].rq_arrival_time);
    while (i > 0 && compare(rq.process_id[i], rq.process_id[(i - 1) / 2]))
    {
        swap(&rq.process_id[i], &rq.process_id[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int remove_rq(int time)
{
    p[rq.process_id[0]].waiting_time += time - p[0].rq_arrival_time;
    rq.size--;
    swap(&rq.process_id[0], &rq.process_id[rq.size]);
    min_heapify(0);
    return rq.process_id[rq.size];
}

void add_wq(int x, int time)
{
    int i = wq.size++;
    wq.process_id[i] = x;
    p[x].wq_arrival_time = time;
    if (wq.size == 1)
    {
        p[wq.process_id[0]].wq_start_time = time;
    }
}

int remove_wq(int time)
{
    int x = wq.process_id[0];
    if (time - p[x].wq_start_time >= p[x].IO_burst)
    {
        p[x].waiting_time += p[x].wq_start_time - p[x].wq_arrival_time;
        for (int j = 0; j < wq.size - 1; j++)
            swap(&wq.process_id[j], &wq.process_id[j + 1]);
        if (wq.size > 1)
        {
            p[wq.process_id[0]].wq_start_time = time;
        }

        return wq.process_id[wq.size - 1];
    }
    return -1;
}

void run(int n)
{
    int time = 0;
    while (1)
    {
        mid_term_scheduler(time, -1);
        long_term_scheduler(n, time);
        int process_id = short_term_scheduler(time);
        if (process_id == -1)
        {
            if (job_no < n || wq.size)
            {
                time++;
                continue;
            }
            else
                break;
        }
        if (p[process_id].response_time == -1)
            p[process_id].response_time = time - p[process_id].arrival_time;
        int t = min(p[process_id].remaining_time, p[process_id].IO_call);
        p[process_id].remaining_time -= t;
        for (int i = time; i < time + t; i++)
        {
            mid_term_scheduler(i, -1);
            long_term_scheduler(n, i);
        }
        time += t;
        if (p[process_id].remaining_time > 0)
        {
            mid_term_scheduler(time, process_id);
        }
        else
        {
            printf("Process %d terminated at time %d.\n", process_id, time);
            p[process_id].completion_time = time;
        }
    }
}

int main()
{
    int n = intialize();
    job_schedule(n);
    run(n);
    printf("\n\n");
    calculate(n,2);
}