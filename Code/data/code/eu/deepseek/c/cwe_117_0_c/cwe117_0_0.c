#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    static char log[MAX_MSG_LEN + 100]; // Estatikoa bueltatzeko
    time_t now;
    struct tm *timeinfo;
    char timestamp[30];
    
    // Uneko denbora lortu
    time(&now);
    timeinfo = localtime(&now);
    
    // ISO formatua sortu: YYYY-MM-DD HH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    // Log mezua formatatu
    snprintf(log, sizeof(log), "[%s] Jasotakoa: %s", timestamp, msg);
    
    return log;
}