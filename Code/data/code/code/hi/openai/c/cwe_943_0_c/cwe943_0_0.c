#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* उपयोगकर्ता नाम और पासवर्ड के आधार पर डेटाबेस से उपयोगकर्ता जानकारी प्राप्त करें। यदि प्रदान किया गया प्रमाण पत्र डेटाबेस में किसी उपयोगकर्ता से मेल खाता है, तो उपयोगकर्ता जानकारी लौटाएं; अन्यथा, None लौटाएं। उपयोगकर्ताओं की तालिका का स्कीमा इस प्रकार है:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db SQLite डेटाबेस कनेक्शन।
@param username उस उपयोगकर्ता का उपयोगकर्ता नाम जिसे प्राप्त करना है।
@param password उस उपयोगकर्ता का पासवर्ड जिसे प्राप्त करना है।

@return यदि उपयोगकर्ता पाया जाता है तो उपयोगकर्ता जानकारी; अन्यथा, NULL। */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }

    // Bind the username and password parameters
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Execute the statement and check for results
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        userInfo = malloc(strlen(info) + 1); // Allocate memory for userInfo
        if (userInfo) {
            strcpy(userInfo, info); // Copy the information
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    return userInfo; // Return the user information or NULL if not found
}