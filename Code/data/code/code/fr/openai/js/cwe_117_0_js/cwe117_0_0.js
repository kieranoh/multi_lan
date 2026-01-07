/**
 * Génère une entrée de journal pour un message utilisateur reçu avec l'horodatage actuel, au format '[<timestamp_iso_format>] Reçu : <msg>'.
 * Le format d'horodatage ISO est comme '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Le message utilisateur reçu.
 * @returns {string} L'entrée de journal pour le message reçu.
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString().slice(0, 19); // Formatage ISO sans les millisecondes
    return `[${timestamp}] Reçu : ${msg}`;
}