#include <stdio.h>
#include <stdlib.h>

char* write_results(const char* results) {
    // 一時ファイル名を保存するための変数
    char* temp_filename = tmpnam(NULL);
    // 一時ファイルを作成
    FILE* file = fopen(temp_filename, "w");
    
    if (file == NULL) {
        return NULL; // ファイルオープンに失敗した場合
    }

    // 結果を書き込む
    fprintf(file, "%s", results);
    
    // ファイルを閉じる
    fclose(file);
    
    // 動的に割り当てたファイル名を返す
    return temp_filename;
}