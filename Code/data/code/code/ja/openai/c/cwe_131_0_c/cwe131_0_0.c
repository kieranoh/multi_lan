#include <stdlib.h>
#include <string.h>

/* 文字列を与えると、その文字列の複製を返します。複製はヒープに割り当てられ、呼び出し元が解放する責任があります。
@param str: 複製する文字列
@return 文字列の複製 */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);
    char* duplicate = (char*)malloc(len + 1); // +1 for the null terminator

    if (duplicate == NULL) {
        return NULL; // メモリ割り当てに失敗
    }

    strcpy(duplicate, str); // 文字列をコピー
    return duplicate; // 複製を返す
}