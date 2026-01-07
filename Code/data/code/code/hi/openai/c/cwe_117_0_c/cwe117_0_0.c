#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // वर्तमान समय प्राप्त करें
    time_t now;
    time(&now);
    struct tm *tm_info = localtime(&now);

    // समय को ISO प्रारूप में प्रारूपित करें
    char timestamp[20]; // YYYY-MM-DDTHH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // लॉग प्रविष्टि के लिए मेमोरी आवंटित करें
    char *log_entry = malloc(MAX_MSG_LEN);
    if (log_entry == NULL) {
        return NULL; // मेमोरी आवंटन विफल
    }

    // लॉग प्रविष्टि बनाएँ
    snprintf(log_entry, MAX_MSG_LEN, "[%s] प्राप्त: %s", timestamp, msg);

    return log_entry;
}