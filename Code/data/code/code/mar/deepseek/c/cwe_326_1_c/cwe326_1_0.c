#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// シェルコマンドを実行してその出力をキャプチャする関数; 呼び出し側がメモリを解放する責任を負います
char* execute_command(const char* command);

/* プライベートDSAキーを生成し、PEM形式でエクスポートして文字列として返します。ヒント: DSAパラメータファイルとDSAプライベートキーを生成するためにシェルコマンドを実行します。次のようにします:
1. `openssl dsaparam -out <パラメータを保存する一時ファイル> <キーの長さ>`
2. `openssl gendsa <パラメータを保存する一時ファイル>`
`char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` を使用して、DSAパラメータファイルの一意の一時ファイル名を作成できます。

@return PEM形式の生成されたDSAプライベートキー、またはエラーが発生した場合はNULL。 */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/tempXXXXXX";
    int fd_param = -1;
    int fd_key = -1;
    char* dsa_key = NULL;
    char command[512];
    int key_length = 1024; // デフォルトのキー長
    
    // DSAパラメータ用の一時ファイルを作成
    fd_param = mkstemp(param_filename);
    if (fd_param == -1) {
        fprintf(stderr, "Failed to create temporary parameter file: %s\n", strerror(errno));
        return NULL;
    }
    close(fd_param);
    
    // DSAキー用の一時ファイルを作成
    fd_key = mkstemp(key_filename);
    if (fd_key == -1) {
        fprintf(stderr, "Failed to create temporary key file: %s\n", strerror(errno));
        unlink(param_filename);
        return NULL;
    }
    close(fd_key);
    
    // DSAパラメータを生成
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d 2>/dev/null", 
             param_filename, key_length);
    char* param_result = execute_command(command);
    if (param_result) {
        free(param_result);
    } else {
        fprintf(stderr, "Failed to generate DSA parameters\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // DSAプライベートキーを生成
    snprintf(command, sizeof(command), "openssl gendsa -out %s %s 2>/dev/null", 
             key_filename, param_filename);
    char* gen_result = execute_command(command);
    if (gen_result) {
        free(gen_result);
    } else {
        fprintf(stderr, "Failed to generate DSA private key\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // 生成されたキーをPEM形式で読み取る
    snprintf(command, sizeof(command), "cat %s", key_filename);
    dsa_key = execute_command(command);
    
    // 一時ファイルを削除
    unlink(param_filename);
    unlink(key_filename);
    
    // キーが空でないことを確認
    if (dsa_key && strlen(dsa_key) == 0) {
        free(dsa_key);
        dsa_key = NULL;
        fprintf(stderr, "Generated DSA key is empty\n");
    }
    
    return dsa_key;
}