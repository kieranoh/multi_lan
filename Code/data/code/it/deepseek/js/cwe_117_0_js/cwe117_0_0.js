/* * Genera un'entrata di log per un messaggio utente ricevuto con il timestamp attuale, nel formato '[<timestamp_iso_format>] Ricevuto: <msg>'.
 * Il formato del timestamp ISO è simile a '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Il messaggio utente ricevuto.
 * @returns {string} L'entrata di log per il messaggio ricevuto. */
function generate_receive_log(msg) {
    // Ottieni il timestamp corrente in formato ISO (senza millisecondi)
    const now = new Date();
    const timestamp = now.toISOString().split('.')[0];
    
    // Costruisci e restituisci la stringa di log nel formato specificato
    return `[${timestamp}] Ricevuto: ${msg}`;
}