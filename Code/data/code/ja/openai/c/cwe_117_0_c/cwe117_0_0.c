#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 現在のタイムスタンプで受信したユーザーメッセージのログエントリを生成します。フォーマットは '[<timestamp_iso_format>] 受信: <msg>' です。
@param msg 受信したユーザーメッセージ。
@return 受信したメッセージのログエントリ。 */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    // タイムスタンプ用のバッファを準備
    char timestamp[20];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // ISO 8601形式でタイムスタンプを生成
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // ログエントリのフォーマットサイズを計算
    size_t msg_len = strlen(msg);
    size_t log_len = strlen(timestamp) + strlen(" 受信: ") + msg_len + 3; // 2文字のクォートと終端文字

    // ログエントリ用メモリを確保
    char *log_entry = (char *)malloc(log_len);
    if (log_entry == NULL) {
        return NULL; // メモリ確保に失敗
    }

    // ログエントリを生成
    snprintf(log_entry, log_len, "[%s] 受信: %s", timestamp, msg);

    return log_entry; // 生成したログエントリを返す
}