/*
 * Copyright 2012 
 *  Steven Maresca <steve@zentific.com>
 *
 * This program serves no useful purpose; that was intentional.
 *
 */

#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static jmp_buf bandaid;

static void catch_segv() {
    longjmp(bandaid, 1);
}

static void adios(int dummy) {
    printf("\nByebye, you\n");
    exit(1);
}

int main() {
    int *iterate_me = NULL;
    unsigned int i = 0;

    char *ticktock[2];
    ticktock[0] = "tick";
    ticktock[1] = "tock";

    signal(SIGINT, adios);
    signal(SIGSEGV, catch_segv);
    if (setjmp(bandaid) == 0) {
        printf("%s\n", ticktock[i%2]);
        i++;
        *iterate_me = 11;
    } else {
        sleep(1);
        printf("%s\n", ticktock[i%2]);
        i++;
        longjmp(bandaid, 0);
    }
    return 0;
}
