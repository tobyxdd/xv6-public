#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// custom syscall added for CS 202 Lab 1
// one integer parameter with value 1, 2 or 3
// 1 - count of the processes in the system
// 2 - count of the total number of system calls that the current process has made so far
// 3 - number of memory pages the current process is using
int sys_info(void)
{
  int option;
  if (argint(0, &option) < 0)
    return -1;

  // TODO implement the options
  if (option == 1)
  {
    return proccount();
  }
  else if (option == 2)
  {
    return procsyscallcount();
  }
  else if (option == 3)
  {
    return (myproc()->sz) / PGSIZE;
  }
  else
  {
    return -1;
  }
}

// custom syscall added for CS 202 Lab 2
// set current process ticket value
// for lottery/stride scheduler
int sys_tickets(void)
{
  int tickets;
  if (argint(0, &tickets) < 0)
    return -1;

  myproc()->tickets = tickets;
  return 0;
}

// custom syscall added for CS 202 Lab 2
// dump ticks info
int sys_ticks(void)
{
  return procticksdump();
}