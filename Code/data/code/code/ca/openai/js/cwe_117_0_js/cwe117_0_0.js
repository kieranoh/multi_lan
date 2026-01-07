/**
 * Genera una entrada de registre per a un missatge d'usuari rebut amb la marca de temps actual, en el format '[<timestamp_iso_format>] Rebut: <msg>'.
 * El format de marca de temps ISO és com '2021-09-15T14:30:00'.
 *
 * @param {string} msg - El missatge d'usuari rebut.
 * @returns {string} L'entrada de registre per al missatge rebut.
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString();
    return `[${timestamp}] Rebut: ${msg}`;
}