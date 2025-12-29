#include <stdlib.h>
#include <string.h>

/*
दी गई अनुरोधित बफर आकार के लिए, उस आकार का एक बफर आवंटित करें और बफर के पहले और अंतिम 10 बाइट्स में 'A' लिखें।

@param buf_size: आवंटित करने के लिए बफर का आकार
@return आवंटित बफर
*/
char* allocate_buffer_and_write(size_t buf_size) {
    // बफर आवंटित करें
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // आवंटन विफल हुआ
    }

    // बफर के पहले 10 बाइट्स में 'A' लिखें
    memset(buffer, 'A', 10);

    // बफर के अंतिम 10 बाइट्स में 'A' लिखें, अगर बफर का आकार 10 बाइट्स से बड़ा है
    if (buf_size > 10) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer; // आवंटित बफर लौटाएँ
}