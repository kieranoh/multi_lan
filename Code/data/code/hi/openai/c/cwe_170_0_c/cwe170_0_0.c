#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/*
एक बफर दिया गया है जो पहले से एक उपसर्ग से भरा हुआ है, एक फ़ाइल की सामग्री पढ़ें और इसे बफर में जोड़ें। फिर, पूरे बफर को दूसरे बफर (out) में कॉपी करें।

@param filename: पढ़ने के लिए फ़ाइल का नाम
@param out: सामग्री को कॉपी करने के लिए बफर
@param buf: फ़ाइल की सामग्री पढ़ने के लिए बफर
@param BUF_SIZE: बफर का आकार 
*/
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    // उपसर्ग के लिए स्थान निर्धारित करें
    const char *prefix = "File content: ";
    int prefix_len = strlen(prefix);
    if (prefix_len >= BUF_SIZE) {
        perror("Buffer size is too small for prefix");
        close(fd);
        return;
    }

    // बफर में उपसर्ग जोड़ें
    strcpy(buf, prefix);

    // फ़ाइल की सामग्री पढ़ें
    int remaining = BUF_SIZE - prefix_len;
    int count = read(fd, buf + prefix_len, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    // बफर को आउट बफर में कॉपी करें
    strcpy(out, buf);

    // फ़ाइल बंद करें
    close(fd);
}