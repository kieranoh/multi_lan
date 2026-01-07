#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    if (results == NULL) {
        return NULL;
    }

    // अस्थायी फ़ाइल नाम के लिए टेम्पलेट बनाएं
    char template[] = "/tmp/results_XXXXXX";
    
    // mkstemp का उपयोग करके एक अद्वितीय अस्थायी फ़ाइल बनाएं
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // परिणामों को फ़ाइल में लिखें
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    // फ़ाइल डिस्क्रिप्टर को बंद करें
    close(fd);
    
    if (written != (ssize_t)len) {
        // लिखने में विफल रहा, फ़ाइल हटाएं
        unlink(template);
        return NULL;
    }
    
    // फ़ाइल नाम की प्रतिलिपि बनाने के लिए मेमोरी आवंटित करें
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template);
        return NULL;
    }
    
    strcpy(filename, template);
    return filename;
}