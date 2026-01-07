#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 現在のシステム時刻を取得
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // タイムスタンプをISOフォーマットでフォーマット
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(std::localtime(&time_t_now), "%Y-%m-%dT%H:%M:%S");
    
    // 完全なログエントリを構築
    std::ostringstream log_entry_stream;
    log_entry_stream << "[" << timestamp_stream.str() << "] 受信: " << msg;
    
    return log_entry_stream.str();
}