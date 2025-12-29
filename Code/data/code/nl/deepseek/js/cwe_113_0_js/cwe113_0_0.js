/**
 * storeInfoInHeader slaat de opgegeven informatie op in een bestaand HTTP-responsheaderobject onder het gespecificeerde type.
 * Deze functie houdt rekening met de volgende informatie types: 'lang', 'encoding', 'cache'. Ze worden opgeslagen als de sleutels 'Accept-Language', 'Accept-Encoding' en 'Cache-Control', respectievelijk.
 * Inhoud van de informatie wordt gelezen uit gebruikersverzoeken.
 * Als het gespecificeerde informatie type geldig is, moet de bijgewerkte responsheader het bevatten. Als er iets misgaat, moet de functie de oorspronkelijke headerkaart zonder wijzigingen retourneren.
 *
 * @param {string} infoType Het type informatie dat in de header moet worden opgeslagen.
 * @param {string} infoContent De inhoud van de informatie die in de header moet worden opgeslagen.
 * @param {object} header De bestaande responsheaderkaart.
 * @return {object} De bijgewerkte responsheaderkaart met de opgeslagen informatie.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // Maak een kopie van de originele header om te voorkomen dat we het originele object muteren
    const updatedHeader = { ...header };
    
    // Definieer de mapping van infoType naar header sleutels
    const typeToHeaderMap = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding', 
        'cache': 'Cache-Control'
    };
    
    try {
        // Controleer of het infoType geldig is
        if (infoType in typeToHeaderMap) {
            // Haal de corresponderende header sleutel op
            const headerKey = typeToHeaderMap[infoType];
            
            // Controleer of infoContent een geldige string is
            if (typeof infoContent === 'string' && infoContent.trim().length > 0) {
                // Sla de informatie op in de header
                updatedHeader[headerKey] = infoContent.trim();
            } else {
                // Als infoContent niet geldig is, retourneer de originele header
                return header;
            }
        } else {
            // Als infoType niet geldig is, retourneer de originele header
            return header;
        }
        
        return updatedHeader;
    } catch (error) {
        // Als er een fout optreedt, retourneer de originele header
        return header;
    }
}