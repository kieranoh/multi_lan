#include <string.h>
#include <stdio.h>

#define HEADER_SIZE 10

typedef struct {
    char key[50];
    char value[100];
} HeaderEntry;

typedef struct {
    HeaderEntry entries[HEADER_SIZE];
    int count;
} HeaderDict;

// ヘッダ辞書内のキーのインデックスを見つける関数。見つからない場合は-1を返す。
int find_header_index(const HeaderDict *header, const char *key) {
    for (int i = 0; i < header->count; i++) {
        if (strcmp(header->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

/* 指定されたタイプの下で、既存のレスポンスヘッダ辞書に提供された情報を格納します。
この関数は、次の情報タイプを考慮します: 'lang', 'encoding', 'cache'。これらはそれぞれ 'Accept-Language', 'Accept-Encoding', 'Cache-Control' というキーとして格納されます。
情報の内容はユーザーのリクエストから読み取られます。
指定された情報タイプが有効であれば、更新されたレスポンスヘッダにはそれが含まれている必要があります。何か問題が発生した場合、関数は変更なしに元のヘッダ辞書を返すべきです。

@param info_type ヘッダに格納する情報のタイプ。
@param info_content ヘッダに格納する情報の内容。
@param header 既存のレスポンスヘッダ辞書。

@return 格納された情報を持つ更新されたレスポンスヘッダ辞書。 */
HeaderDict* store_info_in_header(const char *info_type, const char *info_content, HeaderDict *header) {
    // 入力パラメータのNULLチェック
    if (info_type == NULL || info_content == NULL || header == NULL) {
        return header;
    }
    
    // ヘッダ辞書のカウントが有効範囲内かチェック
    if (header->count < 0 || header->count > HEADER_SIZE) {
        return header;
    }
    
    const char *header_key = NULL;
    
    // 情報タイプに基づいて適切なヘッダキーを決定
    if (strcmp(info_type, "lang") == 0) {
        header_key = "Accept-Language";
    } else if (strcmp(info_type, "encoding") == 0) {
        header_key = "Accept-Encoding";
    } else if (strcmp(info_type, "cache") == 0) {
        header_key = "Cache-Control";
    } else {
        // 無効な情報タイプの場合は元のヘッダを返す
        return header;
    }
    
    // 情報内容の長さチェック（valueフィールドのサイズを考慮）
    if (strlen(info_content) >= 100) {
        return header;
    }
    
    // 既存のエントリを検索
    int index = find_header_index(header, header_key);
    
    if (index != -1) {
        // 既存のエントリを更新
        strncpy(header->entries[index].value, info_content, 99);
        header->entries[index].value[99] = '\0'; // 終端文字を保証
    } else {
        // 新しいエントリを追加（容量チェック）
        if (header->count >= HEADER_SIZE) {
            return header; // 容量不足の場合は元のヘッダを返す
        }
        
        // キーをコピー
        strncpy(header->entries[header->count].key, header_key, 49);
        header->entries[header->count].key[49] = '\0'; // 終端文字を保証
        
        // 値をコピー
        strncpy(header->entries[header->count].value, info_content, 99);
        header->entries[header->count].value[99] = '\0'; // 終端文字を保証
        
        // カウントを増加
        header->count++;
    }
    
    return header;
}