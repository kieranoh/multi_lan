#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* एक प्राप्त उपयोगकर्ता संदेश के लिए एक लॉग प्रविष्टि उत्पन्न करें जिसमें वर्तमान समय मुहर हो, प्रारूप में '[<timestamp_iso_format>] प्राप्त: <msg>'.

@param msg प्राप्त उपयोगकर्ता संदेश।

@return प्राप्त संदेश के लिए लॉग प्रविष्टि। */
char* generate_receive_log(const char *msg) {
    // ISO 8601 timestamp format: YYYY-MM-DDTHH:MM:SS
    const int TIMESTAMP_LEN = 20;
    const int PREFIX_LEN = 12; // "[YYYY-MM-DDTHH:MM:SS] प्राप्त: "
    const int MAX_LOG_LEN = PREFIX_LEN + MAX_MSG_LEN + 1;
    
    // Get current time
    time_t raw_time;
    struct tm *time_info;
    char timestamp[TIMESTAMP_LEN];
    
    time(&raw_time);
    time_info = localtime(&raw_time);
    
    // Format timestamp as ISO 8601
    strftime(timestamp, TIMESTAMP_LEN, "%Y-%m-%dT%H:%M:%S", time_info);
    
    // Calculate required buffer size
    size_t msg_len = strlen(msg);
    size_t total_len = 1 + TIMESTAMP_LEN + 2 + 9 + msg_len + 1; // '[' + timestamp + ']' + space + "प्राप्त: " + msg + null terminator
    
    // Allocate memory for log entry
    char *log_entry = (char*)malloc(total_len * sizeof(char));
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Construct log entry
    snprintf(log_entry, total_len, "[%s] प्राप्त: %s", timestamp, msg);
    
    return log_entry;
}