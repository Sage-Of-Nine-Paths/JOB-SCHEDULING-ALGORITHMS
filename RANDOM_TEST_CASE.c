#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 30

void generate_random_process_set(int num_processes)
{
    FILE *fp;
    int i;

    // Open the file in write mode (overwrite if it exists)
    fp = fopen("input.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Write the header for the input format
    fprintf(fp, "Write input in following format below it:\n");
    fprintf(fp, "Arrival_time\tCPU_Burst\tI/O_Burst\tI/O_Call\n");

    // Seed the random number generator
    srand(time(0));

    // Generate and write random process data to the file
    for (i = 0; i < num_processes; i++)
    {
        int arrival_time = rand() % (MAX_VALUE + 1);
        int cpu_burst = rand() % (MAX_VALUE + 1);
        int io_burst = rand() % (MAX_VALUE + 1);
        int io_call = rand() % (MAX_VALUE + 1);
        fprintf(fp, "%d\t%d\t%d\t%d\n", arrival_time, cpu_burst, io_burst, io_call);
    }

    // Close the file
    fclose(fp);

    printf("Process set generated and written to input.txt.\n");
}

int main()
{
    int num_test_cases;

    // Ask the user for the number of test cases
    printf("Enter the number of test cases: ");
    scanf("%d", &num_test_cases);

    // Generate process sets for each test case
    for (int i = 0; i < num_test_cases; i++)
    {
        printf("Generating process set for test case %d...\n", i + 1);
        generate_random_process_set(i + 1);
    }

    return 0;
}