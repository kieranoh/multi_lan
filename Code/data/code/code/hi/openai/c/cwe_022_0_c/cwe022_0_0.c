#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // पूर्ण पथ बनाने के लिए मेमोरी आवंटित करें
    size_t path_length = strlen(filename) + strlen(dir_path) + 2; // 1 फॉर '/' और 1 फॉर '\0'
    char *full_path = (char *)malloc(path_length);
    if (full_path == NULL) {
        return NULL; // मेमोरी आवंटन विफल
    }
    
    // पूर्ण पथ का निर्माण करें
    snprintf(full_path, path_length, "%s/%s", dir_path, filename);
    
    // फ़ाइल खोलें
    FILE *file = fopen(full_path, "r");
    free(full_path); // पूर्ण पथ अब आवश्यक नहीं है, इसे मुक्त करें
    
    if (file == NULL) {
        return strdup(""); // यदि फ़ाइल नहीं मिली या पढ़ने में त्रुटि, तो खाली स्ट्रिंग लौटाएं
    }
    
    // फ़ाइल की सामग्री पढ़ें
    fseek(file, 0, SEEK_END); // फ़ाइल के अंत में जाएं
    long file_size = ftell(file); // फ़ाइल का आकार प्राप्त करें
    rewind(file); // फ़ाइल के आरंभ में लौटें
    
    // सामग्री के लिए मेमोरी आवंटित करें
    char *content = (char *)malloc(file_size + 1); // +1 नल समाप्ति के लिए
    if (content == NULL) {
        fclose(file);
        return NULL; // मेमोरी आवंटन विफल
    }
    
    // फ़ाइल की सामग्री पढ़ें
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // नल समाप्ति जोड़ें
    fclose(file); // फ़ाइल बंद करें
    
    return content; // सामग्री लौटाएं
}