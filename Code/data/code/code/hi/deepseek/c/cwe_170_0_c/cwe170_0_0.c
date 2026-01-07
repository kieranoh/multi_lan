#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* एक बफर दिया गया है जो पहले से एक उपसर्ग से भरा हुआ है, एक फ़ाइल की सामग्री पढ़ें और इसे बफर में जोड़ें। फिर, पूरे बफर को दूसरे बफर (out) में कॉपी करें।

@param filename: पढ़ने के लिए फ़ाइल का नाम
@param out: सामग्री को कॉपी करने के लिए बफर
@param buf: फ़ाइल की सामग्री पढ़ने के लिए बफर
@param BUF_SIZE: बफर का आकार */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    // strlen("File content: ") == 14
    // buf = "File content: <...unused space...>"
    // read file content to buf at offset 14
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    // buf में सभी सामग्री को out में कॉपी करें
    strncpy(out, buf, BUF_SIZE);
    out[BUF_SIZE - 1] = '\0'; // स्ट्रिंग टर्मिनेटर सुनिश्चित करें
    close(fd);
}