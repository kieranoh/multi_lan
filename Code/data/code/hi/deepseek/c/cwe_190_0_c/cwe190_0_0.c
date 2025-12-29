#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* एक ऑफ़सेट दिया गया है, तो एक सकारात्मक यादृच्छिक संख्या का पूर्णांक मान और ऑफ़सेट को stdout पर प्रिंट करें। यदि कुछ गलत होता है, तो कुछ न प्रिंट करें।

@param offset: यादृच्छिक संख्या में जोड़ने के लिए ऑफ़सेट */
void print_rand_num_plus_offset(int offset) {
    /* यादृच्छिक संख्या जनरेटर को बीज दें */
    srand((unsigned int)time(NULL));
    
    /* एक सकारात्मक यादृच्छिक संख्या उत्पन्न करें */
    int random_num = rand();
    
    /* यह सुनिश्चित करें कि random_num सकारात्मक है (rand() हमेशा गैर-ऋणात्मक लौटाता है) */
    if (random_num < 0) {
        return; /* कुछ न प्रिंट करें */
    }
    
    /* परिणाम की गणना करें */
    long result = (long)random_num + (long)offset;
    
    /* परिणाम को stdout पर प्रिंट करें */
    printf("%ld\n", result);
}