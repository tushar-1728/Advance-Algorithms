#include "dyntable_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>


// call this function to start a nanosecond-resolution timer
struct timespec timer_start(){
	struct timespec start_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
	return start_time;
}

// call this function to end a timer, returning nanoseconds elapsed as a long
static long timer_end(struct timespec start_time){
	struct timespec end_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	long diffInNanos = (end_time.tv_sec - start_time.tv_sec) * (long)1e9 + (end_time.tv_nsec - start_time.tv_nsec);
	return diffInNanos;
}

//simple test case push 10 elements pops 5 elements (check if they are correct) and pushes 5 more elements and pops 
// all 10 elements( check if they are correct) and pops one more time to test empty condition
bool test_case_1() {
    printf("test case 1 started.\n");
    void* dt = make_new_dynamic_table(10);
    int ele;
    struct timespec vartime;
    long time_elapsed_nanos;
    // pushes 1..10
    for(int i = 1; i <= 10; ++i) {
        vartime = timer_start();
        push_back(&dt, i);
        time_elapsed_nanos = timer_end(vartime);
        printf("push_back: %d time taken %ld\n", i, time_elapsed_nanos);
    }
    // pops 10..5
    for(int i = 10; i >= 6; --i) {
        vartime = timer_start();
        ele = pop_back(&dt);
        time_elapsed_nanos = timer_end(vartime);
        if(i != ele) {
            printf("pop_back failed expected %d got %d time taken %ld\n", i, ele, time_elapsed_nanos);
            return false;
        }
        printf("pop_back expected %d got %d time taken %ld\n", i, ele, time_elapsed_nanos);
    }
    // pushes 1..5
    for(int i = 1; i <= 5; ++i) {
        vartime = timer_start();
        push_back(&dt, i);
        time_elapsed_nanos = timer_end(vartime);
        printf("push_back: %d time taken %ld\n", i, time_elapsed_nanos);
    }
    // pops all elements in the table
    for(int i = 10; i >= 1; --i) {
        vartime = timer_start();
        ele = pop_back(&dt);
        time_elapsed_nanos = timer_end(vartime);
        if((((i-1)%5)+1) != ele) {
            printf("pop_back failed expected %d got %d time taken %ld\n", ((i-1)%5)+1, ele, time_elapsed_nanos);
            return false;
        }
        printf("pop_back expected %d got %d time taken %ld\n", ((i-1)%5)+1, ele, time_elapsed_nanos);
    }
    vartime = timer_start();
    ele = pop_back(&dt);
    time_elapsed_nanos = timer_end(vartime);
    if(-1 != ele) {
        printf("pop_back failed expected %d got %d time taken %ld\n", -1, ele, time_elapsed_nanos);
        return false;
    }
    printf("pop_back expected %d got %d time taken %ld\n", -1, ele, time_elapsed_nanos);
    printf("test case 1 completed.\n");
    return true;
}

// random test that is read from a file
// reading a 1 means pushing that number next to it
// reading a 0 means poping a number and comparing it to number next to it
bool test_case_2() {
    printf("test case 2 started.\n");
    FILE *fp = fopen("dt_operations1.txt", "r");
    void* dt = make_new_dynamic_table(10);
    int n;
    int op, num;
    struct timespec vartime;
    long time_elapsed_nanos;
    fscanf(fp, "%d", &n);
    printf("%d\n", n);
    for(int i = 1; i <= n; ++i) {
        fscanf(fp, "%d %d", &op, &num);
        //push
        if(op == 1) {
            vartime = timer_start();
            push_back(&dt, num);
            time_elapsed_nanos = timer_end(vartime);
            printf("push_back: %d time taken %ld\n", num, time_elapsed_nanos);
        }
        //pop
        else {
            vartime = timer_start();
            int ele = pop_back(&dt);
            time_elapsed_nanos = timer_end(vartime);
            if(num != ele) {
                printf("pop_back failed expected %d got %d time taken %ld\n", num, ele, time_elapsed_nanos);
                return false;
            }
            printf("pop_back expected %d got %d time taken %ld\n", num, ele, time_elapsed_nanos);
        }
    }
    printf("test case 2 completed.\n");
    return true;
}

bool test_case_3() {
    printf("test case 3 started.\n");
    FILE *fp = fopen("dt_operations2.txt", "r");
    void* dt = make_new_dynamic_table(10);
    int n;
    int op, num;
    struct timespec vartime;
    long time_elapsed_nanos;
    fscanf(fp, "%d", &n);
    printf("%d\n", n);
    for(int i = 1; i <= n; ++i) {
        fscanf(fp, "%d %d", &op, &num);
        //push
        if(op == 1) {
            vartime = timer_start();
            push_back(&dt, num);
            time_elapsed_nanos = timer_end(vartime);
            printf("push_back: %d time taken %ld\n", num, time_elapsed_nanos);
        }
        //pop
        else {
            vartime = timer_start();
            int ele = pop_back(&dt);
            time_elapsed_nanos = timer_end(vartime);
            if(num != ele) {
                printf("pop_back failed expected %d got %d time taken %ld\n", num, ele, time_elapsed_nanos);
                return false;
            }
            printf("pop_back expected %d got %d time taken %ld\n", num, ele, time_elapsed_nanos);
        }
    }
    printf("test case 3 completed.\n");
    return true;
}

//pass the first argument as something you want to print in the log or the file that stores the results as a seperator like a name or USN
int main(int argc, char** argv) {
    FILE *fp = fopen("./results.txt", "a");
    fprintf(fp, "%s\n", argv[0]);
    printf("%s\n", argv[0]);

    bool test_1_results = test_case_1();
    fprintf(fp,"test 1 results %s\n",test_1_results ? "passed" : "failed");

    bool test_2_results = test_case_2();
    fprintf(fp,"test 2 results %s\n",test_2_results ? "passed" : "failed");

    bool test_3_results = test_case_3();
    fprintf(fp,"test 3 results %s\n",test_3_results ? "passed" : "failed");

    fclose(fp);
}
