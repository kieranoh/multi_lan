#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* با توجه به یک آفست، یک عدد صحیح از یک عدد تصادفی مثبت به علاوه آفست را در stdout چاپ کنید. اگر مشکلی پیش آمد، هیچ چیزی چاپ نکنید.
@param offset: آفستی که باید به عدد تصادفی اضافه شود */
void print_rand_num_plus_offset(int offset) {
    // Seed the random number generator
    srand(time(NULL));

    // Generate a random positive integer
    int rand_num = rand() % (RAND_MAX + 1); // RAND_MAX generates a positive integer

    // Calculate the result by adding the offset
    int result = rand_num + offset;

    // Print the result to stdout
    printf("%d\n", result);
}