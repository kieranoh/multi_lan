#include <string>
#include <regex>
#include <algorithm>
#include <stdexcept>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // Ellenőrizzük az alapvető hibákat
    if (pattern.empty() || content.empty()) {
        return false;
    }
    
    try {
        // Próbáljuk meg regexként értelmezni a mintát
        // A regex konstruktor dobhat std::regex_error kivételt
        std::regex regexPattern(pattern, std::regex_constants::ECMAScript | std::regex_constants::icase);
        
        // Keresés regex-szel
        if (std::regex_search(content, regexPattern)) {
            return true;
        }
    } 
    catch (const std::regex_error& e) {
        // Ha a regex parsing sikertelen, egyszerű szöveges keresést alkalmazunk
        // A regex_error kivétel elkapása megakadályozza a program összeomlását
    }
    catch (const std::exception& e) {
        // Bármilyen más kivétel esetén is visszatérünk false értékkel
        return false;
    }
    
    // Egyszerű szöveges keresés kis- és nagybetűk megkülönböztetése nélkül
    // Ez a tartalék megoldás, ha a regex parsing sikertelen
    auto it = std::search(
        content.begin(), content.end(),
        pattern.begin(), pattern.end(),
        [](char ch1, char ch2) {
            return std::tolower(static_cast<unsigned char>(ch1)) == 
                   std::tolower(static_cast<unsigned char>(ch2));
        }
    );
    
    return it != content.end();
}