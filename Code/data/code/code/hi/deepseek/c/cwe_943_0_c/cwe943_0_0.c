#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }
    
    sqlite3_stmt *stmt = NULL;
    char *result = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // प्रिपेयर स्टेटमेंट
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    
    // पैरामीटर बाइंड करें
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    
    // क्वेरी निष्पादित करें
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // userInfo कॉलम से डेटा प्राप्त करें
        const unsigned char *userInfo = sqlite3_column_text(stmt, 0);
        if (userInfo != NULL) {
            // परिणाम की प्रतिलिपि बनाएँ
            result = strdup((const char *)userInfo);
        }
    }
    
    // स्टेटमेंट साफ़ करें
    sqlite3_finalize(stmt);
    
    return result;
}