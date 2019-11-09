#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    printf(1, "mempage count: %d\n", info(3));
    printf(1, "process count: %d\n", info(1));
    printf(1, "syscall count: %d\n", info(2));
    printf(1, "ticks: %d\n", ticks());
    exit();
}