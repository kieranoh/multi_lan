#include <string>
#include <tuple>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Паттерны для проверки email в порядке от наиболее строгого к наименее строгому
    const std::vector<std::pair<std::string, std::string>> patterns = {
        // RFC 5322 Official Standard (упрощенный)
        {
            "RFC5322",
            R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)"
        },
        // Общий паттерн с поддержкой международных доменов (IDN)
        {
            "CommonWithIDN",
            R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)"
        },
        // Базовый паттерн для большинства случаев
        {
            "BasicExtended",
            R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)"
        }
    };

    // Предварительные проверки
    if (email.empty() || email.length() > 254) { // RFC 5321 ограничивает длину 254 символами
        return std::make_tuple(false, "LengthCheck");
    }

    // Проверка на наличие @
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, "NoAtSymbol");
    }

    // Разделение на локальную часть и домен
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);

    // Проверка длины локальной части (RFC 5321: максимум 64 символа)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "LocalPartTooLong");
    }

    // Проверка на двойные точки и специальные символы в начале/конце
    if (local_part.find("..") != std::string::npos ||
        local_part.front() == '.' || local_part.back() == '.' ||
        domain_part.find("..") != std::string::npos ||
        domain_part.front() == '.' || domain_part.back() == '.') {
        return std::make_tuple(false, "InvalidDotSequence");
    }

    // Проверка каждого паттерна
    for (const auto& pattern : patterns) {
        try {
            std::regex email_regex(pattern.second, std::regex_constants::ECMAScript | std::regex_constants::icase);
            if (std::regex_match(email, email_regex)) {
                // Дополнительная проверка доменной части
                if (domain_part.length() > 253) { // Максимальная длина домена
                    return std::make_tuple(false, "DomainTooLong");
                }
                
                // Проверка, что доменная часть содержит хотя бы одну точку
                if (domain_part.find('.') == std::string::npos) {
                    return std::make_tuple(false, "NoDotInDomain");
                }
                
                // Проверка TLD (должен быть минимум 2 символа)
                size_t last_dot = domain_part.find_last_of('.');
                std::string tld = domain_part.substr(last_dot + 1);
                if (tld.length() < 2) {
                    return std::make_tuple(false, "InvalidTLD");
                }
                
                // Проверка, что TLD содержит только буквы
                if (!std::all_of(tld.begin(), tld.end(), [](char c) {
                    return std::isalpha(static_cast<unsigned char>(c));
                })) {
                    return std::make_tuple(false, "InvalidTLDChars");
                }
                
                return std::make_tuple(true, pattern.first);
            }
        } catch (const std::regex_error&) {
            // Пропускаем некорректные regex паттерны
            continue;
        }
    }

    // Если ни один паттерн не подошел, пробуем более либеральную проверку
    {
        std::string liberal_pattern = R"(^[^@\s]+@[^@\s]+\.[^@\s]+$)";
        std::regex liberal_regex(liberal_pattern);
        if (std::regex_match(email, liberal_regex)) {
            // Базовая проверка структуры
            if (domain_part.find('.') != std::string::npos) {
                return std::make_tuple(true, "Liberal");
            }
        }
    }

    return std::make_tuple(false, "NoPatternMatch");
}