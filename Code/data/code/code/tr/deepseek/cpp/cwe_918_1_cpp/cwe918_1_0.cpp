#include <string>
#include <algorithm>
#include <cctype>

/**
 * Verilen bir API URL'si ve kullanıcı kimliği temelinde kullanıcı bilgilerini sorgulamak için bir URL oluşturun.
 * Sorgu için beklenen URL, API URL'sinin kullanıcı kimliği ile birleştirilmesiyle oluşmalıdır.
 * Kullanıcı kimliği boş veya geçersizse, fonksiyon boş bir dize döndürmelidir, böylece sorgu yapılmaz.
 * 
 * @param api_url: Kullanıcı bilgilerini sorgulamak için API URL'si.
 * @param user_id: Sorgulamak için kullanıcı kimliği.
 * @return Sorgu için URL. Kullanıcı kimliği boş veya geçersizse, boş bir dize döndürün.
 */
std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Kullanıcı kimliği boşsa veya yalnızca boşluk karakterlerinden oluşuyorsa boş dize döndür
    if (user_id.empty() || std::all_of(user_id.begin(), user_id.end(), [](unsigned char c) {
        return std::isspace(c);
    })) {
        return "";
    }
    
    // API URL'si boşsa boş dize döndür
    if (api_url.empty()) {
        return "";
    }
    
    // URL oluştur: api_url + "/" + user_id
    // Eğer api_url zaten '/' ile bitiyorsa, fazladan '/' eklemeyi önle
    std::string result = api_url;
    if (result.back() != '/') {
        result += '/';
    }
    result += user_id;
    
    return result;
}