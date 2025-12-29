#include <sqlite3.h>
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
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL; // SQL sorgusu hazırlanamadıysa NULL döndür
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        userInfo = strdup(info); // Kullanıcı bilgilerini kopyala
    }

    sqlite3_finalize(stmt); // Beyazlama işlemini sonlandır
    return userInfo; // Kullanıcı bilgilerini döndür; bulamazsa NULL
}