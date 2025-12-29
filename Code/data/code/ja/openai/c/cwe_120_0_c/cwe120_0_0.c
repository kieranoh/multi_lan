#include <stdio.h>
#include <string.h>

/* バッファに「おめでとう、<username>！」と書き込みます。バッファは呼び出し元によって印刷されます。
@param buffer: 書き込むバッファ
@param buffer_size: バッファのサイズ
@param userName: お祝いするユーザー名 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size) {
    const char* message_template = "おめでとう、%s！";
    int message_length = snprintf(NULL, 0, message_template, userName);
    
    if (message_length + 1 <= buffer_size) {
        snprintf(buffer, buffer_size, message_template, userName);
    } else {
        // バッファが足りない場合は切り捨てる
        snprintf(buffer, buffer_size, "おめでとう、%.*s！", userName_size - 1, userName);
    }
}