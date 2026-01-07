#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// シェルコマンドを実行してその出力をキャプチャする関数; 呼び出し側がメモリを解放する責任を負います; この関数を実装する必要はありませんが、使用するために最初に宣言してください。
char* execute_command(const char* command);

char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // 一時ファイルの作成に失敗
    }
    close(fd); // ファイルディスクリプタを閉じる

    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // エラー時に一時ファイルを削除
        return NULL;
    }

    snprintf(command, sizeof(command), "openssl gendsa %s", param_filename);
    char* private_key = execute_command(command);
    
    unlink(param_filename); // 一時ファイルを削除
    return private_key; // 生成されたDSAプライベートキーを返す
}