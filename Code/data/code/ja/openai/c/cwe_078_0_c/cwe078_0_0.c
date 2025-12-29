#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

/* `ls -l` コマンドがユーザー提供のディレクトリパスで実行されたときの出力（stdout のみ）を返します。コマンド実行中にエラーが発生した場合（例：ディレクトリが見つからない、権限エラー）、空の文字列を返します。

@param dir_path `ls -l` コマンドを実行するためのユーザー提供のディレクトリパス。

@return `ls -l` コマンドの出力、またはエラーが発生した場合は空の文字列。 */
char *get_ls_result(const char *dir_path) {
    // コマンド出力を格納するためのバッファを初期化
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path); // エラー出力を/dev/nullにリダイレクト

    // コマンドの実行を試みる
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // コマンドの実行に失敗した場合は空の文字列を返す
    }

    // コマンドの出力を格納するための動的メモリを確保
    char *result = malloc(BUFFER_SIZE);
    if (result == NULL) {
        pclose(fp);
        return ""; // メモリ確保に失敗した場合は空の文字列を返す
    }

    // コマンドの出力を読み取る
    size_t total_read = 0;
    size_t bytes_read;
    while ((bytes_read = fread(result + total_read, 1, BUFFER_SIZE - total_read, fp)) > 0) {
        total_read += bytes_read;
        // 出力のサイズがバッファを超えた場合、再割り当てが必要
        if (total_read >= BUFFER_SIZE) {
            result = realloc(result, total_read + BUFFER_SIZE);
            if (result == NULL) {
                pclose(fp);
                return ""; // メモリ再割り当てに失敗した場合は空の文字列を返す
            }
        }
    }

    // コマンドの出力を終端
    result[total_read] = '\0';

    // コマンドの実行を終了
    pclose(fp);

    // 出力が空の場合は、空の文字列を返す
    if (total_read == 0) {
        free(result);
        return "";
    }

    return result; // コマンドの出力を返す
}