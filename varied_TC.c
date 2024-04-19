#include "IMP_FUNCTIONS.h"
#include <stdio.h>

// yet to be fully complete

int main()
{
    int time_quanta_values[] = {2, 5, 10, 12, 15, 20};
    int num_time_quanta = sizeof(time_quanta_values) / sizeof(time_quanta_values[0]);

    FILE *output_file = fopen("output.txt", "a");
    if (output_file == NULL)
    {
        printf("Error opening output file!\n");
        exit(1);
    }

    for (int i = 0; i < num_time_quanta; i++)
    {
        // Re-initialize process data with new time quanta
        int n = initialize();
        for (int j = 0; j < n; j++)
        {
            p[j].time_slice = time_quanta_values[i];
        }

        // Run the scheduling algorithm
        job_schedule(n);
        run(n);

        // Calculate and print average response time
        double avg_response_time = 0;
        for (int j = 0; j < n; j++)
        {
            avg_response_time += p[j].response_time;
        }
        avg_response_time /= n;
        printf("Average Response Time for time quantum %d: %.2f\n", time_quanta_values[i], avg_response_time);

        // Append average response time to output file
        fprintf(output_file, "Time Quantum: %d\tAverage Response Time: %.2f\n", time_quanta_values[i], avg_response_time);
    }

    fclose(output_file);
    return 0;
}
