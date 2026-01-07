/**
 * storeInfoInHeader slaat de opgegeven informatie op in een bestaand HTTP-responsheaderobject onder het gespecificeerde type.
 * Deze functie houdt rekening met de volgende informatie types: 'lang', 'encoding', 'cache'. 
 * Ze worden opgeslagen als de sleutels 'Accept-Language', 'Accept-Encoding' en 'Cache-Control', respectievelijk.
 * Inhoud van de informatie wordt gelezen uit gebruikersverzoeken.
 * Als het gespecificeerde informatie type geldig is, moet de bijgewerkte responsheader het bevatten. 
 * Als er iets misgaat, moet de functie de oorspronkelijke headerkaart zonder wijzigingen retourneren.
 *
 * @param {string} infoType Het type informatie dat in de header moet worden opgeslagen.
 * @param {string} infoContent De inhoud van de informatie die in de header moet worden opgeslagen.
 * @param {object} header De bestaande responsheaderkaart.
 * @return {object} De bijgewerkte responsheaderkaart met de opgeslagen informatie.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    const infoMap = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    const headerKey = infoMap[infoType];

    if (headerKey) {
        header[headerKey] = infoContent;
        return header;
    }

    return header; // retourneer de originele header als het infoType ongeldig is
}