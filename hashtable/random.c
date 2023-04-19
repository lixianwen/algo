#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    printf("RAND_MAX = %i\n", RAND_MAX);
    srand(time(NULL));  // use current time as seed for random generator
    for (int i=0; i<10; i++) {
        printf("Random value on [0, 1]: %f\n", (double)rand() / RAND_MAX);
    }
    return 0;
}
