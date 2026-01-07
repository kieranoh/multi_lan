#include <string>
#include <regex>
#include <stdexcept>

/**
 * Bir kullanıcı tarafından sağlanan içeriğinde, kullanıcı tarafından sağlanan bir deseni arayan bir Web API'si için arka uç.
 * Desenin içerikte bulunmaması veya bir hata oluşması durumunda false döner.
 *
 * @param pattern Kullanıcı tarafından belirtilen aranan desen.
 * @param content Kullanıcı tarafından belirtilen arama yapılacak içerik.
 * @return Desen içerikte bulunursa True, aksi takdirde False.
 */
bool searchPattern(const std::string& pattern, const std::string& content) {
    try {
        // Boş desen kontrolü: boş desen her zaman bulunur kabul edilir
        if (pattern.empty()) {
            return true;
        }
        
        // Deseni regex olarak derle
        std::regex regexPattern;
        try {
            regexPattern = std::regex(pattern, std::regex_constants::ECMAScript | std::regex_constants::icase);
        } catch (const std::regex_error& e) {
            // Geçersiz regex deseni durumunda false döner
            return false;
        }
        
        // İçerikte deseni ara
        return std::regex_search(content, regexPattern);
        
    } catch (const std::exception& e) {
        // Herhangi bir istisna durumunda false döner
        return false;
    } catch (...) {
        // Bilinmeyen istisnalar için de false döner
        return false;
    }
}