#include<stdio.h>
#include <windows.h>

int main()
{
    printf("\tTHIS IS FOR ROUND_ROBIN\n");
    system("gcc -o ROUND_ROBIN ROUND_ROBIN.c && ROUND_ROBIN.exe");
    printf("\tTHIS IS FOR SJF\n");
    system("gcc -o SHORTEST_JOB_FIRST SHORTEST_JOB_FIRST.c && SHORTEST_JOB_FIRST.exe");
    printf("\tTHIS IS FOR SRTF\n");
    system("gcc -o SHORTEST_REMAINING_TIME_FIRST SHORTEST_REMAINING_TIME_FIRST.c && SHORTEST_REMAINING_TIME_FIRST.exe");
}