#include <string.h>
#include <stdio.h>

/* バッファに「おめでとう、<username>！」と書き込みます。バッファは呼び出し元によって印刷されます。

@param buffer: 書き込むバッファ
@param buffer_size: バッファのサイズ
@param userName: お祝いするユーザー名 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        if (buffer != NULL && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    const char *prefix = "おめでとう、";
    const char *suffix = "！";
    
    int prefix_len = (int)strlen(prefix);
    int suffix_len = (int)strlen(suffix);
    
    int total_len = prefix_len + userName_size + suffix_len;
    
    if (total_len >= buffer_size) {
        if (buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    strcpy(buffer, prefix);
    strncat(buffer, userName, userName_size);
    strcat(buffer, suffix);
}