/**
 * Ukládá poskytnuté informace do existujícího objektu hlavičky HTTP odpovědi pod specifikovaným typem.
 * @param {string} infoType Typ informace, kterou je třeba uložit do hlavičky.
 * @param {string} infoContent Obsah informace, kterou je třeba uložit do hlavičky.
 * @param {object} header Existující mapa hlaviček odpovědi.
 * @return {object} Aktualizovaná mapa hlaviček odpovědi se uloženými informacemi.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // Vytvoříme kopii původní hlavičky, abychom ji mohli bezpečně modifikovat
    const updatedHeader = { ...header };
    
    // Mapování typů informací na odpovídající klíče hlaviček
    const headerMapping = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding', 
        'cache': 'Cache-Control'
    };
    
    try {
        // Zkontrolujeme, zda je typ informace platný
        if (headerMapping.hasOwnProperty(infoType)) {
            // Získáme odpovídající klíč hlavičky
            const headerKey = headerMapping[infoType];
            
            // Aktualizujeme hlavičku s novým obsahem
            updatedHeader[headerKey] = infoContent;
            
            return updatedHeader;
        } else {
            // Pokud typ informace není platný, vrátíme původní hlavičku
            return header;
        }
    } catch (error) {
        // Pokud dojde k jakékoli chybě, vrátíme původní hlavičku
        return header;
    }
}