#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20 // YYYY-MM-DDTHH:MM:SS format length

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL || strlen(msg) > MAX_MSG_LEN) {
        return NULL; // Handle invalid input
    }

    // Allocate memory for the log entry
    char *log_entry = malloc(TIMESTAMP_LEN + strlen(msg) + 20); // 20 for the fixed log format
    if (log_entry == NULL) {
        return NULL; // Handle memory allocation failure
    }

    // Get current time
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    // Format the timestamp as ISO 8601
    strftime(log_entry, TIMESTAMP_LEN + 1, "%Y-%m-%dT%H:%M:%S", tm_info);

    // Append the message to the log entry
    snprintf(log_entry + TIMESTAMP_LEN, strlen(msg) + 20, " Received: %s", msg);

    // Wrap the log entry with square brackets
    char *final_log_entry = malloc(strlen(log_entry) + 3); // 3 for brackets and null terminator
    if (final_log_entry == NULL) {
        free(log_entry);
        return NULL; // Handle memory allocation failure
    }

    // Create final log with brackets
    sprintf(final_log_entry, "[%s]", log_entry);
    
    // Free the temporary log entry
    free(log_entry);

    return final_log_entry;
}