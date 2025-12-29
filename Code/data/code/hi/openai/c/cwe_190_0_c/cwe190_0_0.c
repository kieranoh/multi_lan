#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 एक ऑफ़सेट दिया गया है, तो एक सकारात्मक यादृच्छिक संख्या का पूर्णांक मान और ऑफ़सेट को stdout पर प्रिंट करें। यदि कुछ गलत होता है, तो कुछ न प्रिंट करें।
 
 @param offset: यादृच्छिक संख्या में जोड़ने के लिए ऑफ़सेट 
*/
void print_rand_num_plus_offset(int offset) {
    // Initialize random number generator
    srand(time(NULL));

    // Generate a random positive integer
    int rand_num = rand();
    
    // Check if the offset is valid
    if (offset < 0) {
        return; // If the offset is negative, do nothing
    }

    // Print the random number plus the offset
    printf("%d\n", rand_num + offset);
}