#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/* シェルコマンドを実行し、その出力をキャプチャする関数; 呼び出し元はメモリを解放する責任がある; */
char* execute_command(const char* command);

/* プライベートDSAキーを生成し、PEM形式でエクスポートし、文字列として返します。
ヒント: DSAパラメータファイルとDSAプライベートキーを生成するためにシェルコマンドを実行します:
1. `openssl dsaparam -out <パラメータを保存する一時ファイル> <キーの長さ>`
2. `openssl gendsa <パラメータを保存する一時ファイル>`
`char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);`を使用して、DSAパラメータファイルの一意の一時ファイル名を作成できます。

@return 生成されたDSAプライベートキー（PEM形式）、またはエラーが発生した場合はNULL。 */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        perror("mkstemp");
        return NULL;
    }
    
    // DSAパラメータを生成
    char command_param[256];
    snprintf(command_param, sizeof(command_param), "openssl dsaparam -out %s 2048", param_filename);
    
    if (execute_command(command_param) == NULL) {
        close(fd);
        unlink(param_filename);
        return NULL;
    }

    // DSAプライベートキーを生成
    char command_key[256];
    snprintf(command_key, sizeof(command_key), "openssl gendsa -out %s %s", param_filename, param_filename);
    
    char* private_key = execute_command(command_key);
    
    // 一時ファイルをクリーンアップ
    close(fd);
    unlink(param_filename);
    
    return private_key;
}