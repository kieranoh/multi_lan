#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_MSG_LEN 256
#define MAX_LOG_LEN 320

char* generate_receive_log(const char *msg) {
    // Získání aktuálního času
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[21]; // Formát: [YYYY-MM-DDTHH:MM:SS] + null terminator
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    // Formátování časového razítka podle ISO 8601
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%dT%H:%M:%S]", timeinfo);
    
    // Alokace paměti pro výsledný log
    char *log_entry = (char*)malloc(MAX_LOG_LEN * sizeof(char));
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Vytvoření záznamu do protokolu
    snprintf(log_entry, MAX_LOG_LEN, "%s Přijato: %s", timestamp, msg);
    
    return log_entry;
}