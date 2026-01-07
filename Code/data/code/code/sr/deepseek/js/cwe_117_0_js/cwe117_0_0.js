/**
 * Generiše zapis u dnevniku za primljenu korisničku poruku sa trenutnim vremenskim pečatom, u formatu '[<timestamp_iso_format>] Primljeno: <msg>'.
 * Vremenski pečat u ISO formatu je poput '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Primljena korisnička poruka.
 * @returns {string} Zapis u dnevniku za primljenu poruku.
 */
function generate_receive_log(msg) {
    // Kreiraj trenutni datum i vreme
    const now = new Date();
    
    // Konvertuj u ISO string i izdvoji deo pre milisekundi (YYYY-MM-DDTHH:MM:SS)
    const isoString = now.toISOString();
    const timestamp = isoString.split('.')[0]; // Uklanja milisekunde i 'Z'
    
    // Formiraj i vrati zapis u dnevniku
    return `[${timestamp}] Primljeno: ${msg}`;
}