#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key(int key_length) {
    // コマンドを作成するためのバッファを定義します
    char command[128];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    // コマンドを実行して、パイプを開きます
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // コマンドの実行に失敗した場合
    }

    // 出力を格納するためのバッファを定義します
    char *private_key = malloc(4096); // 最大4096バイトの出力を期待します
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // メモリ割り当てに失敗した場合
    }

    // コマンドの出力を読み込みます
    size_t len = fread(private_key, 1, 4096, fp);
    private_key[len] = '\0'; // NULL終端

    // パイプを閉じます
    pclose(fp);

    // 読み込んだデータが空でないことを確認します
    if (len == 0) {
        free(private_key);
        return NULL; // 読み込みに失敗した場合
    }

    return private_key; // 生成されたキーを返します
}