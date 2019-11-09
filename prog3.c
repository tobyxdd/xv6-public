#include "types.h"
#include "stat.h"
#include "user.h"

#define TICKETS 10

int main(int argc, char *argv[])
{
    tickets(TICKETS);
    int i, k;
    const int loop = 43000;
    for (i = 0; i < loop; i++)
    {
        asm("nop"); //in order to prevent the compiler from optimizing the for loop
        for (k = 0; k < loop; k++)
        {
            asm("nop");
        }
    }
    printf(1, "prog3 ticks: %d\n", ticks());
    exit();
}