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
    
    // ISO 8601形式のタイムスタンプを取得
    time_t raw_time;
    struct tm *time_info;
    char timestamp[21]; // YYYY-MM-DDTHH:MM:SS + null terminator
    
    time(&raw_time);
    time_info = localtime(&raw_time);
    
    if (time_info == NULL) {
        return NULL;
    }
    
    // ISO 8601形式でタイムスタンプをフォーマット
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", time_info);
    
    // 必要なバッファサイズを計算
    // フォーマット: "[YYYY-MM-DDTHH:MM:SS] 受信: " + msg + null terminator
    size_t prefix_len = strlen("[") + strlen(timestamp) + strlen("] 受信: ");
    size_t msg_len = strlen(msg);
    size_t total_len = prefix_len + msg_len + 1; // +1 for null terminator
    
    // メッセージが長すぎる場合は切り詰める
    if (msg_len > MAX_MSG_LEN) {
        msg_len = MAX_MSG_LEN;
        total_len = prefix_len + msg_len + 1;
    }
    
    // メモリを割り当て
    char *log_entry = (char*)malloc(total_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // ログエントリを構築
    snprintf(log_entry, total_len, "[%s] 受信: ", timestamp);
    
    // メッセージを追加（必要に応じて切り詰め）
    if (strlen(msg) > MAX_MSG_LEN) {
        strncat(log_entry, msg, MAX_MSG_LEN);
    } else {
        strcat(log_entry, msg);
    }
    
    return log_entry;
}