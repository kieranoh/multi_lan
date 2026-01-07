#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Holen des aktuellen Zeitpunkts
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Konvertieren in lokale Zeit
    std::tm local_time = *std::localtime(&time_t_now);
    
    // Erstellen eines Stringstreams für die Formatierung
    std::ostringstream timestamp_stream;
    
    // ISO 8601 Format: YYYY-MM-DDTHH:MM:SS
    timestamp_stream << std::put_time(&local_time, "%Y-%m-%dT%H:%M:%S");
    
    // Zusammenbauen des Protokolleintrags
    std::ostringstream log_entry;
    log_entry << "[" << timestamp_stream.str() << "] Empfangen: " << msg;
    
    return log_entry.str();
}