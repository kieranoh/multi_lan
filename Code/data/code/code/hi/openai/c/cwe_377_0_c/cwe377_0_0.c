#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // अस्थायी फ़ाइल के लिए नाम जनरेट करना
    char tmp_filename[] = "/tmp/resultsXXXXXX"; // XXXXXX के स्थान पर प्रक्रिया ID का उपयोग किया जाएगा
    int fd = mkstemp(tmp_filename);
    
    if (fd == -1) {
        return NULL; // फ़ाइल बनाने में विफलता
    }

    // फ़ाइल में परिणाम लिखें
    if (write(fd, results, strlen(results)) == -1) {
        close(fd);
        unlink(tmp_filename); // फ़ाइल को हटाना
        return NULL;
    }

    // फ़ाइल को बंद करें
    close(fd);
    
    // गतिशील रूप से आवंटित फ़ाइल नाम लौटाएं
    char* filename = malloc(strlen(tmp_filename) + 1);
    if (filename == NULL) {
        unlink(tmp_filename); // तकनिकी विफलता
        return NULL;
    }
    strcpy(filename, tmp_filename);
    
    return filename; // अस्थायी फ़ाइल का नाम लौटाएं
}