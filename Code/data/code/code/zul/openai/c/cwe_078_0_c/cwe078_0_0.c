#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // コマンドを実行するためのバッファを作成
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);

    // コマンドの出力を保存するためのバッファを作成
    char *output = malloc(4096); // 4096バイトのメモリを確保
    if (output == NULL) {
        return ""; // メモリ確保に失敗した場合は空の文字列を返す
    }

    // コマンドを実行して出力を取得
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        free(output);
        return ""; // コマンド実行に失敗した場合は空の文字列を返す
    }

    // 出力を読み取る
    size_t index = 0;
    while (fgets(output + index, 4096 - index, fp) != NULL) {
        index += strlen(output + index);
        if (index >= 4096) {
            break; // バッファのサイズを超えないようにする
        }
    }
    pclose(fp);

    // 出力の最後をNULLで終了させる
    output[index] = '\0';

    // 出力が空の場合は空の文字列を返す
    if (index == 0) {
        free(output);
        return "";
    }

    return output;
}