/**
 * Čuva pružene informacije u postojećem HTTP odgovoru pod određenim tipom.
 * Ova funkcija uzima u obzir sledeće tipove informacija: 'lang', 'encoding', 'cache'.
 * Oni se čuvaju kao ključevi 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', redom.
 * Sadržaj informacija se čita iz korisničkih zahteva. Ako je određeni tip informacija validan,
 * ažurirani odgovor mora ga imati. Ako nešto pođe po zlu, funkcija treba da vrati originalnu
 * mapu zaglavlja bez ikakvih promena.
 *
 * @param {string} infoType Tip informacije koja se čuva u zaglavlju.
 * @param {string} infoContent Sadržaj informacije koja se čuva u zaglavlju.
 * @param {object} header Postojeća mapa zaglavlja odgovora.
 * @return {object} Ažurirana mapa zaglavlja odgovora sa sačuvanim informacijama.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // Provera da li su ulazni parametri validni
    if (typeof infoType !== 'string' || typeof infoContent !== 'string' || 
        typeof header !== 'object' || header === null) {
        return header;
    }
    
    // Kreiranje kopije originalnog zaglavlja kako ne bismo modifikovali original direktno
    let updatedHeader;
    try {
        updatedHeader = { ...header };
    } catch (error) {
        // Ako ne možemo da kopiramo zaglavlje, vratimo original
        return header;
    }
    
    // Mapiranje tipova informacija na odgovarajuća imena zaglavlja
    const headerMapping = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding', 
        'cache': 'Cache-Control'
    };
    
    // Provera da li je tip informacije validan
    if (!headerMapping.hasOwnProperty(infoType)) {
        return header; // Vraćamo original ako tip nije validan
    }
    
    // Dobijanje imena zaglavlja na osnovu tipa
    const headerName = headerMapping[infoType];
    
    // Provera da li je sadržaj informacije validan (nije prazan string)
    if (infoContent.trim() === '') {
        return header; // Vraćamo original ako je sadržaj prazan
    }
    
    // Ažuriranje zaglavlja sa novim sadržajem
    updatedHeader[headerName] = infoContent;
    
    return updatedHeader;
}