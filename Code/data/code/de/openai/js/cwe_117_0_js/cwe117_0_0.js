/**
 * Generiert einen Protokolleintrag für eine empfangene Benutzer Nachricht mit dem aktuellen Zeitstempel im Format '[<timestamp_iso_format>] Empfangen: <msg>'.
 * Zeitstempel-ISO-Format ist wie '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Die empfangene Benutzer Nachricht.
 * @returns {string} Der Protokolleintrag für die empfangene Nachricht.
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString();
    return `[${timestamp}] Empfangen: ${msg}`;
}