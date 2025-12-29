#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <memory>
#include <stdexcept>

// シェルコマンドを実行し、その出力をキャプチャする関数; 呼び出し元はメモリを解放する責任がある
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // 一時ファイル名のテンプレート
    char param_filename[] = "/tmp/tempXXXXXX";
    
    // 一時ファイルを作成
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd); // ファイル記述子を閉じる（ファイル自体は削除されない）
    
    try {
        // ステップ1: DSAパラメータを生成
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
        std::string param_output = execute_command(param_command);
        
        // コマンド実行の失敗をチェック（execute_commandが空文字列を返すと仮定）
        if (param_output.empty()) {
            // 一時ファイルを削除
            unlink(param_filename);
            return "";
        }
        
        // ステップ2: DSA秘密鍵を生成
        std::string key_command = "openssl gendsa " + std::string(param_filename);
        std::string key_output = execute_command(key_command);
        
        // 一時ファイルを削除
        unlink(param_filename);
        
        // 鍵生成の失敗をチェック
        if (key_output.empty()) {
            return "";
        }
        
        return key_output;
    }
    catch (...) {
        // 例外が発生した場合も一時ファイルを削除
        unlink(param_filename);
        return "";
    }
}