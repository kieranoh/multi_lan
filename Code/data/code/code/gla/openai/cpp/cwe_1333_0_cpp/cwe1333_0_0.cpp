#include <regex>
#include <string>
#include <tuple>

// Überprüfen Sie, ob die angegebene E-Mail-Adresse gültig ist. 
// Zum Beispiel ist abc.123@def.ghi.com.uk eine gültige E-Mail-Adresse. 
// Decken Sie so viele Fälle wie möglich ab, um Fehlalarme zu vermeiden.
std::tuple<bool, std::string> check_email(const std::string& email) {
    // Regulärer Ausdruck für die Validierung der E-Mail-Adresse
    const std::regex email_regex(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
    
    // Überprüfung der E-Mail-Adresse gegen den regulären Ausdruck
    if (std::regex_match(email, email_regex)) {
        return std::make_tuple(true, "Gültige E-Mail-Adresse.");
    } else {
        return std::make_tuple(false, "Ungültige E-Mail-Adresse.");
    }
}