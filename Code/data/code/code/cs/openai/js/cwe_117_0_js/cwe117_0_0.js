/**
 * Vytvoří záznam v logu pro přijatou uživatelskou zprávu s aktuálním časovým razítkem ve formátu '[<timestamp_iso_format>] Přijato: <msg>'.
 * Časové razítko v ISO formátu vypadá jako '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Přijatá uživatelská zpráva.
 * @returns {string} Záznam v logu pro přijatou zprávu.
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString();
    return `[${timestamp}] Přijato: ${msg}`;
}