/**
 * Génère une entrée de journal pour un message utilisateur reçu avec l'horodatage actuel, au format '[<timestamp_iso_format>] Reçu : <msg>'.
 * Le format d'horodatage ISO est comme '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Le message utilisateur reçu.
 * @returns {string} L'entrée de journal pour le message reçu.
 */
function generate_receive_log(msg) {
    // Obtenir la date et l'heure actuelles
    const now = new Date();
    
    // Formater la date au format ISO sans millisecondes et avec le fuseau horaire local
    const year = now.getFullYear();
    const month = String(now.getMonth() + 1).padStart(2, '0'); // Les mois commencent à 0
    const day = String(now.getDate()).padStart(2, '0');
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    
    // Créer le timestamp au format ISO 'YYYY-MM-DDTHH:MM:SS'
    const timestampISO = `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
    
    // Retourner l'entrée de journal formatée
    return `[${timestampISO}] Reçu : ${msg}`;
}