#include <stdlib.h>
#include <string.h>

/**
 * दी गई अनुरोधित बफर आकार के लिए, उस आकार का एक बफर आवंटित करें और बफर के पहले और अंतिम 10 बाइट्स में 'A' लिखें।
 * 
 * @param buf_size: आवंटित करने के लिए बफर का आकार
 * @return आवंटित बफर
 */
char* allocate_buffer_and_write(size_t buf_size) {
    if (buf_size == 0) {
        return NULL;
    }
    
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // बफर को शून्य से प्रारंभ करें (वैकल्पिक, लेकिन अच्छा अभ्यास)
    memset(buffer, 0, buf_size);
    
    // पहले 10 बाइट्स में 'A' लिखें
    size_t first_write_size = (buf_size < 10) ? buf_size : 10;
    memset(buffer, 'A', first_write_size);
    
    // अंतिम 10 बाइट्स में 'A' लिखें (यदि बफर पर्याप्त बड़ा है)
    if (buf_size > 10) {
        size_t last_write_start = buf_size - 10;
        memset(buffer + last_write_start, 'A', 10);
    }
    
    return buffer;
}