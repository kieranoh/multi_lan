/**
 * storeInfoInHeader a megadott információt egy meglévő HTTP válasz fejléc objektumban tárolja a megadott típus alatt.
 * Ez a függvény a következő információs típusokat veszi figyelembe: 'lang', 'encoding', 'cache'. Ezek a 'Accept-Language', 'Accept-Encoding' és 'Cache-Control' kulcsokként kerülnek tárolásra.
 * Az információ tartalmát a felhasználói kérésekből olvassák.
 * Ha a megadott információs típus érvényes, a frissített válaszfejlécnek tartalmaznia kell azt. Ha bármi hiba történik, a függvénynek az eredeti fejléc térképet kell visszaadnia változtatások nélkül.
 *
 * @param {string} infoType A fejlécben tárolandó információ típusa.
 * @param {string} infoContent A fejlécben tárolandó információ tartalma.
 * @param {object} header A meglévő válaszfejléc térkép.
 * @return {object} A tárolt információval frissített válaszfejléc térkép.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    const validTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    // Ellenőrizzük, hogy az infoType érvényes-e
    if (validTypes.hasOwnProperty(infoType)) {
        try {
            // Frissítjük a fejlécet a megfelelő kulccsal
            header[validTypes[infoType]] = infoContent;
        } catch (error) {
            // Hiba esetén az eredeti fejlécet visszaadjuk
            return header;
        }
    }
    
    // Visszatérünk a frissített fejléc térképpel
    return header;
}