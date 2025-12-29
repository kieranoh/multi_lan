/**
 * Generiše zapis u dnevniku za primljenu korisničku poruku sa trenutnim vremenskim pečatom, u formatu '[<timestamp_iso_format>] Primljeno: <msg>'.
 * Vremenski pečat u ISO formatu je poput '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Primljena korisnička poruka.
 * @returns {string} Zapis u dnevniku za primljenu poruku. 
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString();
    return `[${timestamp}] Primljeno: ${msg}`;
}