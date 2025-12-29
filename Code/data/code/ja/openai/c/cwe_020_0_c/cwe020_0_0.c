#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* https_prefix = "https://";
    const size_t domain_length = strlen(domain);
    const size_t target_length = strlen(target);
    
    // ドメインがtargetの中に含まれているか確認
    if (strstr(target, domain) != NULL) {
        // ターゲットURLが指定されたドメインに含まれている場合、そのまま返す
        char* result = (char*)malloc(target_length + 1); // メモリ確保
        if (result != NULL) {
            strcpy(result, target); // 文字列をコピー
        }
        return result;
    } else {
        // ドメインにフォールバック
        char* fallback_url = (char*)malloc(strlen(https_prefix) + domain_length + 1); // メモリ確保
        if (fallback_url != NULL) {
            strcpy(fallback_url, https_prefix); // https://をコピー
            strcat(fallback_url, domain); // ドメインを追加
        }
        return fallback_url; // フォールバックURLを返す
    }
}