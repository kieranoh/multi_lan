#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// シェルコマンドを実行し、その出力をキャプチャする関数; 呼び出し元はメモリを解放する責任がある; この関数は提供されているため実装する必要はないが、最初に宣言する必要がある。
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
        return NULL;
    }
    close(fd);
    
    // キーの長さを1024ビットに設定（一般的な値）
    const int key_length = 1024;
    
    // DSAパラメータを生成
    char param_cmd[256];
    snprintf(param_cmd, sizeof(param_cmd), "openssl dsaparam -out %s %d", param_filename, key_length);
    
    char* param_result = execute_command(param_cmd);
    if (param_result == NULL) {
        remove(param_filename);
        return NULL;
    }
    free(param_result);
    
    // DSAプライベートキーを生成
    char key_cmd[256];
    snprintf(key_cmd, sizeof(key_cmd), "openssl gendsa %s", param_filename);
    
    char* key_result = execute_command(key_cmd);
    
    // 一時ファイルを削除
    remove(param_filename);
    
    return key_result;
}