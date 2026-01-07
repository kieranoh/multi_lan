#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt = NULL;
    char *userInfo = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // 准备SQL语句
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    
    // 绑定参数
    if (sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    // 执行查询
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // 获取userInfo列的值
        const unsigned char *info = sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            // 分配内存并复制字符串
            userInfo = malloc(strlen((const char *)info) + 1);
            if (userInfo != NULL) {
                strcpy(userInfo, (const char *)info);
            }
        }
    }
    
    // 清理语句
    sqlite3_finalize(stmt);
    
    return userInfo;
}