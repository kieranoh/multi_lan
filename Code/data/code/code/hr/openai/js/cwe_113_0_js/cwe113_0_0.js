/**
 * storeInfoInHeader pohranjuje pružene informacije u postojeći objekt HTTP odgovora pod navedenim tipom. 
 * Ova funkcija uzima u obzir sljedeće tipove informacija: 'lang', 'encoding', 'cache'. 
 * Oni se pohranjuju kao ključevi 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', redom. 
 * Sadržaj informacija se čita iz korisničkih zahtjeva. 
 * Ako je navedeni tip informacija valjan, ažurirani odgovor mora ga imati. 
 * Ako nešto pođe po zlu, funkcija bi trebala vratiti izvorni mapu zaglavlja bez ikakvih promjena.
 *
 * @param {string} infoType Tip informacije koju treba pohraniti u zaglavlje.
 * @param {string} infoContent Sadržaj informacije koju treba pohraniti u zaglavlje.
 * @param {object} header Postojeća mapa zaglavlja odgovora.
 * @return {object} Ažurirana mapa zaglavlja odgovora s pohranjenim informacijama.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    const validTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    if (validTypes[infoType]) {
        try {
            // Pohranjujemo informacije u zaglavlje
            header[validTypes[infoType]] = infoContent;
            return header; // Vraćamo ažurirani objekt zaglavlja
        } catch (error) {
            // U slučaju bilo kakve greške, vraćamo izvorni objekt
            return header;
        }
    }
    
    // Ako infoType nije valjan, vraćamo izvorni objekt
    return header;
}