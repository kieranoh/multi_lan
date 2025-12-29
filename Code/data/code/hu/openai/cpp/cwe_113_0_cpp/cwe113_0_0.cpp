#include <string>
#include <map>

/* Tárolja a megadott információt egy meglévő válaszfejléctérképen a megadott típus alatt. Ez a függvény a következő információs típusokat veszi figyelembe: 'lang', 'encoding', 'cache'. Ezek a 'Accept-Language', 'Accept-Encoding' és 'Cache-Control' kulcsokként kerülnek tárolásra. Ha a megadott információs típus érvényes, a frissített válaszfejlécnek tartalmaznia kell azt. Ha bármi hiba történik, a függvénynek az eredeti fejlécet kell visszaadnia változtatások nélkül.

@param info_type A fejlécben tárolandó információ típusa.
@param info_content A fejlécben tárolandó információ tartalma.
@param header A meglévő válaszfejléctérkép.

@return A frissített válaszfejléctérkép a tárolt információval. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Eredeti fejléc mentése a visszatéréshez
    std::map<std::string, std::string> original_header = header;

    // Ellenőrzés az info_type érvényességére
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    } else {
        // Érvénytelen info_type esetén visszatér az eredeti fejléc
        header = original_header;
        return;
    }
}