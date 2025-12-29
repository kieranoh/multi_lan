#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Haal de huidige tijd op
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ) % 1000;

    // Converteer naar lokale tijd
    std::tm tm_buf;
    #ifdef _WIN32
        localtime_s(&tm_buf, &time_t_now);
    #else
        localtime_r(&time_t_now, &tm_buf);
    #endif

    // Formatteer tijdstempel in ISO-formaat met milliseconden
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_buf, "%Y-%m-%dT%H:%M:%S");
    timestamp_stream << '.' << std::setfill('0') << std::setw(3) << ms.count();

    // Construeer logboekvermelding
    std::ostringstream log_entry;
    log_entry << '[' << timestamp_stream.str() << "] Ontvangen: " << msg;

    return log_entry.str();
}