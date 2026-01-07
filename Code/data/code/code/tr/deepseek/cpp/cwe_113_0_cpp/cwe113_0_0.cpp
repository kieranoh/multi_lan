#include <string>
#include <map>
#include <algorithm>
#include <cctype>

// Yardımcı fonksiyon: string'i küçük harfe çevirir
static std::string to_lower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

/* Verilen bilgiyi belirtilen tür altında mevcut bir yanıt başlık haritasında saklayın. Bu işlev aşağıdaki bilgi türlerini dikkate alır: 'lang', 'encoding', 'cache'. Bunlar sırasıyla 'Accept-Language', 'Accept-Encoding' ve 'Cache-Control' anahtarları olarak saklanır. Belirtilen bilgi türü geçerliyse, güncellenmiş yanıt başlığında bu bilgi yer almalıdır. Herhangi bir sorun çıkarsa, işlev orijinal başlığı herhangi bir değişiklik olmadan döndürmelidir.

@param info_type Başlıkta saklanacak bilgi türü.
@param info_content Başlıkta saklanacak bilginin içeriği.
@param header Mevcut yanıt başlık haritası.

@return Saklanan bilgi ile güncellenmiş yanıt başlık haritası. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Giriş parametrelerini kontrol et
    if (info_type.empty() || info_content.empty()) {
        return; // Boş girişlerde başlığı değiştirme
    }
    
    // Bilgi türünü küçük harfe çevirerek karşılaştırma yap
    std::string lower_type = to_lower(info_type);
    
    // Geçerli bilgi türlerini kontrol et ve uygun başlık anahtarını belirle
    std::string header_key;
    
    if (lower_type == "lang") {
        header_key = "Accept-Language";
    } else if (lower_type == "encoding") {
        header_key = "Accept-Encoding";
    } else if (lower_type == "cache") {
        header_key = "Cache-Control";
    } else {
        // Geçersiz bilgi türü - başlığı değiştirmeden dön
        return;
    }
    
    // Başlık haritasına bilgiyi ekle veya güncelle
    header[header_key] = info_content;
}