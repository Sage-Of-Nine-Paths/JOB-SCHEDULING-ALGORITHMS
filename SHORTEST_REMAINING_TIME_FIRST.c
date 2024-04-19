#include "IMP_FUNCTIONS.h"
#include <time.h>

// All the functions included in the process scheduling of Shortest Remaining time First
void min_heapify(int i);
void add_rq(int x, int time);
int remove_rq(int time);
void add_wq(int x, int time);
int remove_wq(int time);
int compare(int a, int b);

void run(int n)
{
    int time = 0;

    // Till the process is brought into the running queue
    // Infinite loop until all the processes are done
    while (1)
    {
        mid_term_scheduler(time, -1);
        long_term_scheduler(n, time);
        int process_id = short_term_scheduler(time);

        // If there's no process in ready qyeye
        if (process_id == -1)
        {

            // If any left in IO or the ready queue
            if (job_no < n || wq.size)
            {
                time++;
                continue;
            }
            else
                break; //--> As all the processes have completed if conditions does not satisfy
        }

        // Calculating the response time
        if (p[process_id].response_time == -1)
            p[process_id].response_time = time - p[process_id].arrival_time;

        // Taking the min of remaining time  and the time to go for IO
        // When the process is in last phase , if the remaining is less
        // than the IO Call , then we take min
        int t = min(p[process_id].remaining_time, p[process_id].IO_at);
        int i = time;
        for (; i < time + t; i++)
        {

            mid_term_scheduler(i, -1); // Check if any process has to be moved from running to IO
            long_term_scheduler(n, i); // Checks if any process has to be added to ready queue

            // Checking the time to go for IO of the first process in min heap , and
            // the time remaining for the process in the ready queue is shorter
            // than the current process to reach its IO call
            if (p[rq.process_id[0]].IO_call < p[process_id].IO_call + time - i)
            {
                break;
            }
        }

        p[process_id].remaining_time -= i - time;
        p[process_id].IO_at -= i - time;
        time = i;

        // If the process is still remaining
        if (p[process_id].remaining_time > 0)
        {

            // Adding to IO if there is IO remaining
            if (p[process_id].IO_at)
                add_rq(process_id, time);
            else
                mid_term_scheduler(time, process_id);
        }
        else
        {
            printf("Process %i terminated at time %i.\n", process_id, time);
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

int compare(int a, int b)
{
    if (min(p[a].remaining_time, p[a].IO_call) < min(p[b].remaining_time, p[b].IO_call))
        return 1;
    else
        return 0;
}

// For having the process with the minimum IO call
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

// Adding the process in ready queue
// Insertion in a heap
void add_rq(int x, int time)
{
    int i = rq.size++;
    rq.process_id[i] = x;
    p[x].rq_arrival_time = time;
    printf("Process %i has entered into ready queue at time %i.\n", x, p[x].rq_arrival_time);
    while (i > 0 && compare(rq.process_id[i], rq.process_id[(i - 1) / 2]))
    {
        swap(&rq.process_id[i], &rq.process_id[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Deletion in heap
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