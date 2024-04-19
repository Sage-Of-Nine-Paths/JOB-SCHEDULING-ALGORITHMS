#include "IMP_FUNCTIONS.h"
#include <time.h>
int time_slice = 5;
int compare(int a, int b)
{
    if (p[a].time_slice < p[b].time_slice)
        return 1;
    else
        return 0;
}

void add_rq(int x, int time)
{
    int i = rq.size++;
    rq.process_id[i] = x;
    p[x].rq_arrival_time = time;
    printf("Process %d entered into ready queue at time %d.\n", x, p[x].rq_arrival_time);
    while (i > 0)
    {
        if (compare(rq.process_id[i], rq.process_id[i - 1]))
        {
            swap(&rq.process_id[i], &rq.process_id[i - 1]);
        }
        i--;
    }
}

int remove_rq(int time)
{
    int x = rq.process_id[0];
    rq.size--;
    for (int i = 0; i < rq.size; i++)
    {
        rq.process_id[i] = rq.process_id[i + 1];
    }
    p[x].waiting_time += time - p[x].rq_arrival_time;
    return x;
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
        p[x].waiting_time += time - p[x].wq_arrival_time - p[x].IO_burst;
        for (int j = 0; j < wq.size - 1; j++)
            swap(&wq.process_id[j], &wq.process_id[j + 1]);
        if (wq.size)
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
        int t = min(p[process_id].remaining_time, p[process_id].IO_at);
        t = min(t, p[process_id].time_slice);
        p[process_id].time_slice -= t;
        p[process_id].IO_at -= t;
        int i = time;
        for (; i < time + t; i++)
        {
            mid_term_scheduler(i, -1);
            long_term_scheduler(n, i);
        }
        p[process_id].remaining_time -= i - time;
        time = i;
        if (p[process_id].time_slice == 0)
            p[process_id].time_slice = time_slice;
        if (p[process_id].remaining_time > 0)
        {
            if (p[process_id].IO_at)
                add_rq(process_id, time);
            else
                mid_term_scheduler(time, process_id);
        }
        else
        {
            printf("Process %d terminated at time %d.\n", process_id, time);
            p[process_id].completion_time = time;
        }
        if (p[process_id].IO_at == 0)
            p[process_id].IO_at = p[process_id].IO_call;
    }
}

int main()
{
    int n = intialize();
    job_schedule(n);
    run(n);
    calculate(n,3);
}