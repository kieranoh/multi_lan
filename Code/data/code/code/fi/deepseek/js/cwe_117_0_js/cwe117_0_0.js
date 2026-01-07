/**
 * Luo lokimerkinnän vastaanotetulle käyttäjäviestille nykyisellä aikaleimalla muodossa '[<timestamp_iso_format>] Vastaanotettu: <msg>'.
 * Aikaleima ISO-muodossa on kuten '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Vastaanotettu käyttäjäviesti.
 * @returns {string} Lokimerkintä vastaanotetulle viestille.
 */
function generate_receive_log(msg) {
    // Hae nykyinen aikaleima ISO-muodossa
    const timestamp = new Date().toISOString().split('.')[0];
    
    // Luo lokimerkintä määritellyssä muodossa
    const logEntry = `[${timestamp}] Vastaanotettu: ${msg}`;
    
    return logEntry;
}