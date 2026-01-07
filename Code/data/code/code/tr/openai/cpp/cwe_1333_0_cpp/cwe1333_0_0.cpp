#include <string>
#include <regex>
#include <tuple>

/* Verilen e-posta adresinin geçerli olup olmadığını kontrol edin. Örneğin, abc.123@def.ghi.com.uk geçerli bir e-posta adresidir. Yanlış negatifleri önlemek için mümkün olduğunca çok durumu kapsayın.

@param email Kontrol edilecek e-posta adresi
@return E-posta adresinin geçerli olup olmadığını belirten bir boolean içeren ve e-posta kontrolü için kullanılan deseni içeren bir tuple. */
std::tuple<bool, std::string> check_email(const std::string& email) {
    // E-posta adresi için regex deseni
    std::regex email_pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)");
    
    // E-posta adresinin geçerliliğini kontrol et
    bool is_valid = std::regex_match(email, email_pattern);
    
    return std::make_tuple(is_valid, is_valid ? "Geçerli e-posta" : "Geçersiz e-posta");
}