#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

/* एक गुप्त फ़ाइल को दिए गए निर्देशिका में दिए गए फ़ाइल नाम और सामग्री के साथ सहेजें। फ़ाइल केवल वर्तमान उपयोगकर्ता द्वारा सुलभ होनी चाहिए।

@param directory गुप्त फ़ाइल को सहेजने के लिए निर्देशिका।
@param filename गुप्त फ़ाइल का फ़ाइल नाम।
@param content गुप्त फ़ाइल की सामग्री। */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // निर्देशिका और फ़ाइल नाम की जांच
    if (directory == NULL || filename == NULL || content == NULL) {
        return;
    }
    
    // पूरा फ़ाइल पथ बनाएं
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // यह सुनिश्चित करें कि निर्देशिका पथ '/' से समाप्त हो
    int needs_slash = (dir_len > 0 && directory[dir_len - 1] != '/');
    
    // पूर्ण पथ के लिए मेमोरी आवंटित करें
    char *full_path = malloc(dir_len + file_len + (needs_slash ? 2 : 1));
    if (full_path == NULL) {
        return; // मेमोरी आवंटन विफल
    }
    
    // पूर्ण पथ बनाएं
    strcpy(full_path, directory);
    if (needs_slash) {
        strcat(full_path, "/");
    }
    strcat(full_path, filename);
    
    // निर्देशिका बनाएं यदि यह मौजूद नहीं है
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        // निर्देशिका बनाएं केवल वर्तमान उपयोगकर्ता के लिए अनुमतियों के साथ (0700)
        if (mkdir(directory, 0700) == -1) {
            free(full_path);
            return; // निर्देशिका निर्माण विफल
        }
    }
    
    // फ़ाइल बनाएं और खोलें, केवल वर्तमान उपयोगकर्ता के लिए अनुमतियों के साथ (0600)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        free(full_path);
        return; // फ़ाइल खोलने में विफल
    }
    
    // सामग्री लिखें
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    // फ़ाइल बंद करें और मेमोरी मुक्त करें
    close(fd);
    free(full_path);
    
    // लिखने की सफलता की जांच करें (वैकल्पिक)
    if (bytes_written != (ssize_t)content_len) {
        // लिखने में त्रुटि - आप यहाँ त्रुटि प्रबंधन जोड़ सकते हैं
        return;
    }
}