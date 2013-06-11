/* for usleep() */
/* SUSv2 version */
#define _XOPEN_SOURCE 500
#include <unistd.h>

/* for pthread_* */
#include <pthread.h>

/* for exit */
#include <stdlib.h>

/* for puts */
#include <stdio.h>

static int exit_flag = 0;

void* thread_function(void* arg)
{
    int status = 0;
    unsigned int microsecond = 1000000;
    puts("Begin of thread_function");
    while (1) {
        puts("In cycle of thread_function");
        usleep(microsecond);
        if (exit_flag) break;
    }
    puts("End of thread_function");
    pthread_exit((void*)&status);
    /*exit(0);*/
    return 0;
}

int main(void)
{
    pthread_t thread_id;
    void* argument;
    void* status;
    argument = 0;
    status = 0;
    exit_flag = 0;
    puts("Starting thread_function");
    pthread_create(&thread_id, NULL, thread_function, argument);
    puts("Sleeping");
    usleep(5000000);
    puts("Raising exit_flag and waiting for join");
    exit_flag = 1;
    pthread_join(thread_id, &status);
    puts("thread_function ended");

    return 0;
}