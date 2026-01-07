/**
 * storeInfoInHeader speichert die bereitgestellten Informationen in einem vorhandenen HTTP-Antwortheader-Objekt unter dem angegebenen Typ.
 * Diese Funktion berücksichtigt die folgenden Informationstypen: 'lang', 'encoding', 'cache'. Sie werden als Schlüssel 'Accept-Language', 'Accept-Encoding' und 'Cache-Control' gespeichert.
 * Die Informationsinhalte werden aus Benutzeranfragen gelesen.
 * Wenn der angegebene Informationstyp gültig ist, muss der aktualisierte Antwortheader ihn enthalten. Wenn etwas schiefgeht, sollte die Funktion die ursprüngliche Header-Karte ohne Änderungen zurückgeben.
 *
 * @param {string} infoType Der Typ der Informationen, die im Header gespeichert werden sollen.
 * @param {string} infoContent Der Inhalt der Informationen, die im Header gespeichert werden sollen.
 * @param {object} header Die vorhandene Antwortheader-Karte.
 * @return {object} Die aktualisierte Antwortheader-Karte mit den gespeicherten Informationen.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    const validInfoTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    const headerKey = validInfoTypes[infoType];

    if (headerKey) {
        header[headerKey] = infoContent;
        return header;
    }

    return header; // returns the original header if infoType is invalid
}