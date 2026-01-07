/**
 * Vytvoří záznam v logu pro přijatou uživatelskou zprávu s aktuálním časovým razítkem ve formátu '[<timestamp_iso_format>] Přijato: <msg>'.
 * Časové razítko v ISO formátu vypadá jako '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Přijatá uživatelská zpráva.
 * @returns {string} Záznam v logu pro přijatou zprávu.
 */
function generate_receive_log(msg) {
    // Získání aktuálního data a času
    const now = new Date();
    
    // Formátování data do ISO formátu bez milisekund a časového pásma
    const isoString = now.toISOString();
    const timestamp = isoString.split('.')[0]; // Odstranění milisekund
    
    // Sestavení výsledného řetězce logu
    const logEntry = `[${timestamp}] Přijato: ${msg}`;
    
    return logEntry;
}