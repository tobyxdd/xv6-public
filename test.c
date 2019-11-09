// This test case is designed for lottery scheduler
#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{

    int Scheduler(void);

    Scheduler();
    return 0;
}

int Scheduler(void)
{

    int pid;
    int i, j, k, p;

    /*Replace YOUR_SYSCALL_TO_ASSIGN_TICKET with what you implement to assign ticket */
    tickets(60);
    for (i = 0; i < 3; i++)
    {
        pid = fork();
        if (pid > 0)
        {
            continue;
        }
        else if (pid == 0)
        {

            tickets(30 - 10 * i);
            for (p = 0; p < 50; p++)
            {
                for (j = 0; j < 1000; j++)
                {
                    for (k = 0; k < 50000; k++)
                    {
                        asm("nop");
                    }
                }
                ticks();
            }
            printf(1, "\n  child# %d with %d tickets has finished!  \n", getpid(), 30 - 10 * i);
            exit();
        }
        else
        {
            printf(2, "  \n  Error  \n ");
        }
    }

    if (pid > 0)
    {
        for (i = 0; i < 3; i++)
        {
            wait();
        }
    }
    exit();
    return 0;
}