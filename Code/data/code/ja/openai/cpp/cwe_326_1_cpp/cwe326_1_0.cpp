#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>

// シェルコマンドを実行し、その出力をキャプチャする関数; 呼び出し元はメモリを解放する責任がある;
std::string execute_command(const std::string& command);

// プライベートDSAキーを生成し、PEM形式でエクスポートし、文字列として返します。
std::string create_dsa_key() {
    // 一意の一時ファイル名を生成
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return nullptr; // エラー発生
    }
    close(fd);

    // DSAパラメータの生成
    std::string command_param = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    if (execute_command(command_param).empty()) {
        unlink(param_filename); // 一時ファイルを削除
        return nullptr; // エラー発生
    }

    // DSAプライベートキーの生成
    std::string command_key = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(command_key);

    // 一時ファイルを削除
    unlink(param_filename);

    // 生成されたプライベートキーを返す
    return private_key;
}