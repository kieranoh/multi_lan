#include <ctype.h>
#include <string.h>

/* ユーザー入力の文字列から末尾の空白を削除します。文字列はその場で変更されるべきです。 */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    /* 末尾の空白文字を探す */
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    /* 新しい終端を設定 */
    str[i + 1] = '\0';
}