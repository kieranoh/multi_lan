/**
 * Generira zapis u dnevniku za primljenu korisničku poruku s trenutnim vremenskim oznakom, u formatu '[<timestamp_iso_format>] Primljeno: <msg>'.
 * Vremenska oznaka u ISO formatu je poput '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Primljena korisnička poruka.
 * @returns {string} Zapis u dnevniku za primljenu poruku.
 */
function generate_receive_log(msg) {
    // Dohvati trenutni datum i vrijeme
    const now = new Date();
    
    // Generiraj ISO format vremenske oznake (bez milisekundi)
    const timestamp = now.toISOString().split('.')[0];
    
    // Sastavi i vrati zapis u dnevniku
    return `[${timestamp}] Primljeno: ${msg}`;
}