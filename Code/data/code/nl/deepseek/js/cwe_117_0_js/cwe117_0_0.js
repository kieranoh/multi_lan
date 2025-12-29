/**
 * Genereert een logboekvermelding voor een ontvangen gebruikersbericht met de huidige tijdstempel, 
 * in het formaat '[<timestamp_iso_format>] Ontvangen: <msg>'.
 * Tijdstempel ISO-formaat is zoals '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Het ontvangen gebruikersbericht.
 * @returns {string} De logboekvermelding voor het ontvangen bericht.
 */
function generate_receive_log(msg) {
    // Genereer huidige tijdstempel in ISO-formaat (zonder milliseconden)
    const now = new Date();
    const timestamp = now.toISOString().split('.')[0];
    
    // Formatteer de logboekvermelding volgens het gevraagde formaat
    return `[${timestamp}] Ontvangen: ${msg}`;
}