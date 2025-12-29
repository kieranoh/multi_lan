#include <stdio.h>
#include <string.h>

/* ユーザー入力の文字列から末尾の空白を削除します。文字列はその場で変更されるべきです。 */
void trim_spaces(char* str) {
    if (str == NULL) return; // NULLチェック

    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t')) {
        len--; // 空白またはタブを見つけたら、長さを減らす
    }
    str[len] = '\0'; // 新しい長さで文字列を終端
}