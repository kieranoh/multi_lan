#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

/**
 * Gelen bir kullanıcı mesajı için mevcut zaman damgasıyla bir günlük girişi oluşturun,
 * format '[<timestamp_iso_format>] Alındı: <msg>'. Zaman damgası ISO formatı '2021-09-15T14:30:00' gibidir.
 *
 * @param msg Alınan kullanıcı mesajı.
 * @return Alınan mesaj için günlük girişi.
 */
std::string generate_receive_log(const std::string &msg) {
    // Mevcut zamanı al
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // ISO formatına dönüştür (YYYY-MM-DDTHH:MM:SS)
    std::tm tm_now = *std::gmtime(&time_t_now);
    
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_now, "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = timestamp_stream.str();
    
    // Günlük girişini oluştur
    std::string log_entry = "[" + timestamp + "] Alındı: " + msg;
    
    return log_entry;
}