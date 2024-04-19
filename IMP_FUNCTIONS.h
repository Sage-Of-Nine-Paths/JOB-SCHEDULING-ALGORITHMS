#include <stdio.h>
#include <stdlib.h>

struct process
{
    int arrival_time;
    int CPU_burst;
    int IO_call;
    int IO_burst;
    int response_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    int time_slice;
    int rq_arrival_time;
    int wq_arrival_time;
    int wq_start_time;
    int IO_at;
} *p;

struct ready_queue
{
    int size;
    int max_size;
    int process_id[100];
} rq;

struct waiting_queue
{
    int size;
    int max_size;
    int process_id[100];
} wq;

int job_no = 0;
int *job_queue;

int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int compare(int a, int b);
void add_rq(int x, int time);
int remove_rq(int time);
void add_wq(int x, int time);
int remove_wq(int time);

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int intialize()
{
    rq.max_size = 100;
    rq.size = 0;
    wq.max_size = 100;
    wq.size = 0;
    FILE *f = fopen("input.txt", "r");
    if (f == NULL)
    {
        printf("Error");
        exit(1);
    }
    char c;
    fscanf(f, "%*[^\n]");
    c = fgetc(f);
    fscanf(f, "%*[^\n]");
    c = fgetc(f);
    int n = 0;
    int tempo_slice = 5;
    printf("Note: Time quanta will be considered for Round Robin\n");
    printf("Enter time Quanta : ");
    scanf("%d",&tempo_slice);
    while (!feof(f))
    {
        p = (struct process *)realloc(p, (n + 1) * (sizeof(struct process)));
        fscanf(f, " %d", &p[n].arrival_time);
        fscanf(f, " %d", &p[n].CPU_burst);
        fscanf(f, " %d", &p[n].IO_burst);
        fscanf(f, " %d ", &p[n].IO_call);
        p[n].response_time = -1;
        p[n].remaining_time = p[n].CPU_burst;
        p[n].waiting_time = 0;
        p[n].time_slice = tempo_slice;
        p[n].completion_time = -1;
        p[n].rq_arrival_time = -1;
        p[n].wq_arrival_time = -1;
        p[n].wq_start_time = -1;
        p[n].IO_at = p[n].IO_call;
        // printf("%d %d %d %d\n",p[n].arrival_time,p[n].CPU_burst,p[n].IO_burst,p[n].IO_call);
        n++;
    }

    return n;
}

/*
*/

// Assigning pid , and then sorting on the basis of arrival time
void job_schedule(int n)
{
    job_queue = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        job_queue[i] = i;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].arrival_time > p[j].arrival_time)
                swap(job_queue + i, job_queue + j);
        }
    }
}

// add to ready queue
void long_term_scheduler(int n, int time)
{
    while (job_no < n && rq.size != rq.max_size && p[job_queue[job_no]].arrival_time <= time)
    {
        int x = job_queue[job_no++];
        add_rq(x, p[x].arrival_time);
    }
}

int short_term_scheduler(int time)
{
    if (rq.size)
    {
        int x = remove_rq(time);
        printf("Process %d entered into running state at time %d.\n", x, time);
        return x;
    }
    return -1;
}

void mid_term_scheduler(int time, int x)
{
    if (x == -1)
    {
        int y = remove_wq(time);
        if (wq.size && y != -1)
        {
            wq.size--;
            if (rq.size != rq.max_size)
            {
                add_rq(y, time);
            }
            else
            {
                wq.size++;
            }
        }
    }
    else
    {
        printf("Process %d entered into waiting queue at time %d.\n", x, time);
        add_wq(x, time);
    }
}

void calculate(int n, int flag)
{
    double avg_waiting_time = 0, avg_turnaround_time = 0, avg_response_time = 0;
    for (int i = 0; i < n; i++)
    {
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        int k = (p[i].CPU_burst / p[i].IO_call);
        if ((p[i].CPU_burst % p[i].IO_call) == 0)
            k--;
        p[i].waiting_time = p[i].turnaround_time - p[i].CPU_burst - p[i].IO_burst * k;
    }
    for (int i = 0; i < n; i++)
    {
        avg_waiting_time += p[i].waiting_time;
    }
    for (int i = 0; i < n; i++)
    {
        avg_turnaround_time += p[i].turnaround_time;
    }
    for (int i = 0; i < n; i++)
    {
        avg_response_time += p[i].response_time;
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    avg_response_time /= n;

    printf("Process\tWait time\tTurnaround time\tResponse time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n", i + 1, p[i].waiting_time, p[i].turnaround_time, p[i].response_time);
    }
    FILE* output_file;
    if(flag == 1) output_file = fopen("output_round_robin.txt", "w");
    else if(flag == 2) output_file = fopen("output_sjf.txt", "w");
    else if(flag == 3) output_file = fopen("output_srtf.txt", "w");
    if (output_file == NULL) {
        printf("Error opening output file!\n");
        exit(1);
    }

    fprintf(output_file, "Process\tWait time\tTurnaround time\tResponse time\n");
    for (int i = 0; i < n; i++) {
        fprintf(output_file, "%d\t%d\t%d\t%d\n", i + 1, p[i].waiting_time, p[i].turnaround_time, p[i].response_time);
    }


    
    fprintf(output_file, "\nAverage Response Time: %.2f\n", avg_response_time);
    fclose(output_file);
    // printf("%f\n", avg_response_time);
    // printf("%f\n" , avg_waiting_time);
    // printf("%f\n" , avg_turnaround_time);
}