#include <string>
#include <algorithm>
#include <regex>
#include <stdexcept>

/**
 * @brief Zoekt naar een patroon in gegeven inhoud met ondersteuning voor eenvoudige jokertekens.
 * 
 * Deze functie ondersteunt:
 * - Standaard tekstzoeken (exacte overeenkomst)
 * - Jokertekens: '?' voor één willekeurig karakter, '*' voor nul of meer willekeurige karakters
 * - Escaping met '\' voor letterlijke '?' en '*'
 * 
 * @param pattern Het patroon waarnaar gezocht moet worden, kan jokertekens bevatten.
 * @param content De inhoud waarin gezocht moet worden.
 * @return true als het patroon ergens in de inhoud wordt gevonden, false anders.
 * @throws std::invalid_argument als het patroon ongeldige escape-sequenties bevat.
 */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // Als het patroon leeg is, beschouwen we dat als een match (lege string is overal aanwezig)
    if (pattern.empty()) {
        return true;
    }

    // Converteer eenvoudige jokerpatroon naar regex
    std::string regexPattern;
    bool escapeNext = false;
    
    for (size_t i = 0; i < pattern.length(); ++i) {
        char c = pattern[i];
        
        if (escapeNext) {
            // Voeg het karakter letterlijk toe, ongeacht wat het is
            if (c == '?' || c == '*' || c == '\\' || c == '.' || c == '+' || 
                c == '^' || c == '$' || c == '|' || c == '(' || c == ')' || 
                c == '[' || c == ']' || c == '{' || c == '}') {
                regexPattern += '\\';
            }
            regexPattern += c;
            escapeNext = false;
        } else if (c == '\\') {
            // Begin van een escape-sequentie
            if (i + 1 >= pattern.length()) {
                // Onvolledige escape-sequentie aan het einde
                throw std::invalid_argument("Ongeldige escape-sequentie aan het einde van het patroon");
            }
            escapeNext = true;
        } else if (c == '?') {
            // '?' komt overeen met precies één willekeurig karakter
            regexPattern += '.';
        } else if (c == '*') {
            // '*' komt overeen met nul of meer willekeurige karakters
            regexPattern += ".*";
        } else {
            // Normaal karakter: escape regex speciale karakters
            if (c == '.' || c == '+' || c == '^' || c == '$' || c == '|' || 
                c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') {
                regexPattern += '\\';
            }
            regexPattern += c;
        }
    }

    // Als we nog in escape-modus zijn, was er een trailing backslash
    if (escapeNext) {
        throw std::invalid_argument("Ongeldige escape-sequentie aan het einde van het patroon");
    }

    try {
        // Compileer de regex
        std::regex regexObj(regexPattern, std::regex_constants::ECMAScript | std::regex_constants::icase);
        
        // Zoek naar het patroon in de inhoud
        return std::regex_search(content, regexObj);
    } catch (const std::regex_error& e) {
        // Als regex-compilatie mislukt (bijv. door te complex patroon),
        // val terug op eenvoudige string zoeken zonder jokertekens
        // Dit kan gebeuren bij zeer lange of complexe patronen
        
        // Controleer eerst op eenvoudige exacte match
        if (pattern.find('?') == std::string::npos && 
            pattern.find('*') == std::string::npos &&
            pattern.find('\\') == std::string::npos) {
            // Geen jokertekens, gebruik eenvoudige zoekopdracht
            return content.find(pattern) != std::string::npos;
        }
        
        // Val terug op een eenvoudige lineaire zoekopdracht met jokerondersteuning
        return simpleWildcardSearch(pattern, content);
    }
}

/**
 * @brief Hulpfunctie voor eenvoudige jokerzoekopdracht zonder regex.
 * 
 * Deze functie implementeert een DP (Dynamic Programming) benadering
 * voor patroonmatching met jokertekens '?' en '*'.
 * 
 * @param pattern Het patroon met jokertekens.
 * @param content De inhoud waarin gezocht moet worden.
 * @return true als het patroon ergens in de inhoud wordt gevonden, false anders.
 */
bool simpleWildcardSearch(const std::string& pattern, const std::string& content) {
    size_t m = pattern.length();
    size_t n = content.length();
    
    // DP-tabel: dp[i][j] = true als pattern[0..i-1] matcht met content[0..j-1]
    std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
    
    // Leeg patroon matcht met lege inhoud
    dp[0][0] = true;
    
    // Leeg patroon matcht alleen met lege inhoud, niet met niet-lege inhoud
    // (behalve als we substrings overwegen, maar dat wordt hieronder afgehandeld)
    
    // Voor '*' aan het begin van het patroon
    for (size_t i = 1; i <= m; ++i) {
        if (pattern[i - 1] == '*') {
            dp[i][0] = dp[i - 1][0];
        }
    }
    
    // Vul de DP-tabel
    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            if (pattern[i - 1] == '*') {
                // '*' kan:
                // 1. Overeenkomen met nul karakters (gebruik dp[i-1][j])
                // 2. Overeenkomen met één of meer karakters (gebruik dp[i][j-1])
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            } else if (pattern[i - 1] == '?' || pattern[i - 1] == content[j - 1]) {
                // '?' matcht met elk karakter, of karakters komen exact overeen
                dp[i][j] = dp[i - 1][j - 1];
            }
            // Anders blijft dp[i][j] false
        }
    }
    
    // We moeten controleren of het patroon overeenkomt met ELKE substring van de inhoud
    // Dit doen we door te kijken of er een j is zodat dp[m][j] true is
    for (size_t j = 0; j <= n; ++j) {
        if (dp[m][j]) {
            return true;
        }
    }
    
    return false;
}