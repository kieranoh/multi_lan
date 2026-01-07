/*
 * Genera un'entrata di log per un messaggio utente ricevuto con il timestamp attuale, nel formato '[<timestamp_iso_format>] Ricevuto: <msg>'.
 * Il formato del timestamp ISO è simile a '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Il messaggio utente ricevuto.
 * @returns {string} L'entrata di log per il messaggio ricevuto.
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString();
    return `[${timestamp}] Ricevuto: ${msg}`;
}