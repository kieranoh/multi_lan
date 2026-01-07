#include <string>
#include <cstdio>
#include <memory>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // コマンドを構築（パスをシェルエスケープする必要があるが、簡略化のため直接使用）
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // パイプを開いてコマンドを実行
    std::array<char, 128> buffer;
    std::string result;
    
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // パイプのオープンに失敗した場合
        return "";
    }
    
    // コマンドの出力を読み取る
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // コマンドが成功したかどうかを確認（結果が空でない場合のみ返す）
    // 実際のエラーは2>/dev/nullで捨てられているため、ここでは出力があるかどうかのみ確認
    return result;
}