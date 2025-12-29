/**
 * Genereert een logboekvermelding voor een ontvangen gebruikersbericht met de huidige tijdstempel, in het formaat '[<timestamp_iso_format>] Ontvangen: <msg>'.
 * Tijdstempel ISO-formaat is zoals '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Het ontvangen gebruikersbericht.
 * @returns {string} De logboekvermelding voor het ontvangen bericht.
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString().slice(0, 19); // Verkrijg de huidige tijdstempel in ISO-formaat zonder de milliseconden en tijdzone-informatie
    return `[${timestamp}] Ontvangen: ${msg}`; // Genereer de logboekvermelding
}