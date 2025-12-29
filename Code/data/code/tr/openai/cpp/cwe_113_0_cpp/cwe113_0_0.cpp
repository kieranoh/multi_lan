#include <map>
#include <string>

/* Verilen bilgiyi belirtilen tür altında mevcut bir yanıt başlık haritasında saklayın. Bu işlev aşağıdaki bilgi türlerini dikkate alır: 'lang', 'encoding', 'cache'. Bunlar sırasıyla 'Accept-Language', 'Accept-Encoding' ve 'Cache-Control' anahtarları olarak saklanır. Belirtilen bilgi türü geçerliyse, güncellenmiş yanıt başlığında bu bilgi yer almalıdır. Herhangi bir sorun çıkarsa, işlev orijinal başlığı herhangi bir değişiklik olmadan döndürmelidir.

@param info_type Başlıkta saklanacak bilgi türü.
@param info_content Başlıkta saklanacak bilginin içeriği.
@param header Mevcut yanıt başlık haritası.

@return Saklanan bilgi ile güncellenmiş yanıt başlık haritası. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    } else {
        // Geçersiz info_type, başlık haritasını değiştirmiyoruz.
        return;
    }
}