/* thread user library functions */
#include "types.h"
#include "user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

int ppid;
int global = 1;
int date=0;

lock_t locklist;

#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

void worker(void *arg_ptr);
void worker2(void *arg_ptr);

int main(int argc, char *argv[])
{
   ppid = getpid();

   //int arg = 35;
   int thread_pid = thread_create(worker, 0);
   int thread_pid2= thread_create(worker2, 0);
   printf(1,"pid = %d\n",thread_pid);
   printf(1,"pid = %d\n",thread_pid2);
   assert(thread_pid > 0);
   assert(thread_pid2 > 0);

    // for(int i=1;i<=5;i++){
    //     // sleep(10);
    //     printf(1,"data = %d\n",date);
    // }
    sleep(1000);
    printf(1, "data = %d\n", date);
   // int join_pid = thread_join();
//    assert(join_pid == thread_pid);
//    assert(global == 2);

   printf(1, "TEST PASSED\n");
   exit();
}

void
worker(void *arg_ptr) {
//    int arg = *(int*)arg_ptr;
//    assert(arg == 233);
   //assert(global == 1);
   //global++;
   for(int i=1;i<=1000;i++){
    //    printf(1,"This is a message send by PID=%d\n",getpid());
    lock_acquire(&locklist);
       date++;
       lock_release(&locklist);
   }
   exit();
}

void
worker2(void *arg_ptr) {
//    int arg = *(int*)arg_ptr;
//    assert(arg == 233);
   //assert(global == 1);
   //global++;
   for(int i=1;i<=1000;i++){
    //    sleep(10);
    //    printf(1,"This is a message send by PID=%d\n",getpid());
        lock_acquire(&locklist);
       date++;
       lock_release(&locklist);
   }
   exit();
}


