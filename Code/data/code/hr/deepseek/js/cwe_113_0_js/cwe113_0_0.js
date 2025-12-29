/**
 * Pohranjuje pružene informacije u postojeći objekt HTTP odgovora pod navedenim tipom.
 * @param {string} infoType Tip informacije koju treba pohraniti u zaglavlje.
 * @param {string} infoContent Sadržaj informacije koju treba pohraniti u zaglavlje.
 * @param {object} header Postojeća mapa zaglavlja odgovora.
 * @return {object} Ažurirana mapa zaglavlja odgovora s pohranjenim informacijama.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // Provjera valjanosti ulaznih parametara
    if (typeof infoType !== 'string' || typeof infoContent !== 'string' || 
        typeof header !== 'object' || header === null) {
        return header;
    }
    
    // Stvaranje kopije originalnog zaglavlja kako ne bismo modificirali original
    const updatedHeader = { ...header };
    
    // Mapiranje tipova informacija na odgovarajuća zaglavlja
    const headerMapping = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding', 
        'cache': 'Cache-Control'
    };
    
    // Provjera je li tip informacija valjan
    if (headerMapping.hasOwnProperty(infoType)) {
        const headerKey = headerMapping[infoType];
        
        // Provjera je li infoContent prazan string ili nedostaje
        if (infoContent && infoContent.trim() !== '') {
            updatedHeader[headerKey] = infoContent.trim();
        } else {
            // Ako je sadržaj prazan, vraćamo originalno zaglavlje bez promjena
            return header;
        }
    } else {
        // Ako tip informacija nije valjan, vraćamo originalno zaglavlje bez promjena
        return header;
    }
    
    return updatedHeader;
}