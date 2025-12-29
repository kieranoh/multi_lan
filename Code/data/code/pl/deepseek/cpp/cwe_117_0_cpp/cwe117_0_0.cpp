#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Pobierz aktualny czas systemowy
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Konwertuj na strukturę tm dla formatowania
    std::tm tm_now = *std::gmtime(&time_t_now);
    
    // Utwórz strumień do formatowania
    std::ostringstream oss;
    
    // Formatuj datę i czas w formacie ISO 8601
    oss << std::put_time(&tm_now, "%Y-%m-%dT%H:%M:%S");
    
    // Dodaj milisekundy dla większej precyzji
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    // Dodaj milisekundy do znacznika czasu (opcjonalnie, jeśli potrzebne)
    // oss << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();
    
    // Zbuduj końcowy wpis dziennika
    std::string log_entry = "[" + oss.str() + "] Odebrano: " + msg;
    
    return log_entry;
}