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
    // Erstelle eine tiefe Kopie des Headers, um Mutationen zu vermeiden
    const updatedHeader = JSON.parse(JSON.stringify(header));
    
    // Definiere die Mapping-Tabelle für Informationstypen zu Header-Schlüsseln
    const typeToHeaderMap = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    };
    
    try {
        // Überprüfe, ob der infoType in der Mapping-Tabelle existiert
        if (typeToHeaderMap.hasOwnProperty(infoType)) {
            // Hole den entsprechenden Header-Schlüssel
            const headerKey = typeToHeaderMap[infoType];
            
            // Setze den Header mit dem neuen Inhalt
            updatedHeader[headerKey] = infoContent;
            
            return updatedHeader;
        } else {
            // Wenn der infoType ungültig ist, gib die ursprüngliche Header-Karte zurück
            return JSON.parse(JSON.stringify(header));
        }
    } catch (error) {
        // Bei einem Fehler gib die ursprüngliche Header-Karte zurück
        return JSON.parse(JSON.stringify(header));
    }
}