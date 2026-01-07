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
    // Ellenőrizzük, hogy a header paraméter érvényes objektum-e
    if (!header || typeof header !== 'object' || Array.isArray(header)) {
        // Ha érvénytelen, adjuk vissza az eredeti headert (vagy egy új üres objektumot)
        return header || {};
    }
    
    try {
        // Létrehozunk egy másolatot a header objektumból, hogy ne módosítsuk az eredetit
        const updatedHeader = { ...header };
        
        // Az infoType alapján meghatározzuk a megfelelő fejléc kulcsot
        let headerKey;
        switch (infoType) {
            case 'lang':
                headerKey = 'Accept-Language';
                break;
            case 'encoding':
                headerKey = 'Accept-Encoding';
                break;
            case 'cache':
                headerKey = 'Cache-Control';
                break;
            default:
                // Ha az infoType nem érvényes, adjuk vissza az eredeti headert
                return header;
        }
        
        // Ellenőrizzük, hogy az infoContent érvényes string-e
        if (typeof infoContent !== 'string' || infoContent.trim() === '') {
            // Ha érvénytelen, adjuk vissza az eredeti headert
            return header;
        }
        
        // Tároljuk az információt a header objektumban
        updatedHeader[headerKey] = infoContent.trim();
        
        return updatedHeader;
    } catch (error) {
        // Ha bármilyen hiba történik, adjuk vissza az eredeti headert
        return header;
    }
}