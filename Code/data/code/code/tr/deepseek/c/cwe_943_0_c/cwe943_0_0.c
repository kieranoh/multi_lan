#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Verilen kullanıcı adı ve şifreye göre veritabanından kullanıcı bilgilerini al. Eğer sağlanan kimlik bilgileri veritabanındaki bir kullanıcıyla eşleşiyorsa, kullanıcı bilgilerini döndür; aksi takdirde None döndür. Kullanıcılar tablosunun şeması aşağıdaki gibidir:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db SQLite veritabanı bağlantısı.
@param username Alınacak kullanıcının kullanıcı adı.
@param password Alınacak kullanıcının şifresi.

@return Kullanıcı bulunursa kullanıcı bilgileri; aksi takdirde NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }
    
    sqlite3_stmt *stmt = NULL;
    char *result = NULL;
    
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    
    rc = sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    rc = sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const char *userInfo = (const char *)sqlite3_column_text(stmt, 0);
        if (userInfo != NULL) {
            result = malloc(strlen(userInfo) + 1);
            if (result != NULL) {
                strcpy(result, userInfo);
            }
        }
    }
    
    sqlite3_finalize(stmt);
    return result;
}