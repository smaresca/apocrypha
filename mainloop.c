#include <stdio.h>
#include <setjmp.h>
#include <time.h>
#include <unistd.h>

static inline void rewindme(jmp_buf *squareone) { if(squareone) longjmp(*squareone, 1); }
#define _begin_ __attribute__((cleanup(rewindme))) jmp_buf squareone; setjmp(squareone); 

int main(int argc, char **argv){
    _begin_

    time_t now = time(NULL);
    printf("hello! %s\n", ctime(&now));
    sleep(1);

    return 0;
}

