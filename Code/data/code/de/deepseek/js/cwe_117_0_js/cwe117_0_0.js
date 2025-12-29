/**
 * Generiert einen Protokolleintrag für eine empfangene Benutzer Nachricht mit dem aktuellen Zeitstempel im Format '[<timestamp_iso_format>] Empfangen: <msg>'.
 * Zeitstempel-ISO-Format ist wie '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Die empfangene Benutzer Nachricht.
 * @returns {string} Der Protokolleintrag für die empfangene Nachricht.
 */
function generate_receive_log(msg) {
    // Erstelle einen neuen Date-Objekt für den aktuellen Zeitpunkt
    const now = new Date();
    
    // Formatierung des ISO-Zeitstempels ohne Millisekunden
    const isoString = now.toISOString();
    const timestamp = isoString.split('.')[0]; // Entfernt Millisekunden
    
    // Erstelle den Protokolleintrag im gewünschten Format
    const logEntry = `[${timestamp}] Empfangen: ${msg}`;
    
    return logEntry;
}