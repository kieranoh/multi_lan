/**
 * storeInfoInHeader lagrar den angivna informationen i ett befintligt HTTP-svarshuvudobjekt under den angivna typen.
 * Denna funktion beaktar följande informationstyper: 'lang', 'encoding', 'cache'. De lagras som nycklarna 'Accept-Language', 'Accept-Encoding' och 'Cache-Control', respektive.
 * Informationsinnehållet läses från användarförfrågningar.
 * Om den angivna informationstypen är giltig måste det uppdaterade svarshuvudet ha den. Om något går fel bör funktionen returnera den ursprungliga huvudkartan utan några ändringar.
 *
 * @param {string} infoType Typen av information som ska lagras i huvudet.
 * @param {string} infoContent Innehållet av informationen som ska lagras i huvudet.
 * @param {object} header Den befintliga svarshuvudkartan.
 * @return {object} Den uppdaterade svarshuvudkartan med den lagrade informationen.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // Validera att header är ett giltigt objekt
    if (typeof header !== 'object' || header === null) {
        return header;
    }

    // Skapa en kopia av det ursprungliga huvudet för att undvika mutation
    const updatedHeader = { ...header };
    
    // Mappning av informationstyper till HTTP-huvudnycklar
    const typeToHeaderMap = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    };

    try {
        // Kontrollera om infoType är giltig
        if (typeToHeaderMap.hasOwnProperty(infoType)) {
            const headerKey = typeToHeaderMap[infoType];
            
            // Validera att infoContent är en sträng
            if (typeof infoContent === 'string' && infoContent.trim() !== '') {
                updatedHeader[headerKey] = infoContent.trim();
            } else {
                // Om infoContent inte är giltigt, returnera originalhuvudet
                return header;
            }
        } else {
            // Om infoType inte är giltig, returnera originalhuvudet
            return header;
        }
        
        return updatedHeader;
    } catch (error) {
        // Vid eventuella fel, returnera originalhuvudet
        return header;
    }
}