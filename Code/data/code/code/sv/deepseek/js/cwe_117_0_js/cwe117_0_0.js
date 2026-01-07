/**
 * Genererar en loggpost för ett mottaget användarmeddelande med aktuell tidsstämpel, i formatet '[<timestamp_iso_format>] Mottaget: <msg>'.
 * Tidsstämpel ISO-format är som '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Det mottagna användarmeddelandet.
 * @returns {string} Loggposten för det mottagna meddelandet.
 */
function generate_receive_log(msg) {
    // Skapa en tidsstämpel i ISO-format (endast datum och tid, utan tidszon)
    const now = new Date();
    const timestamp = now.toISOString().split('.')[0]; // Tar bort millisekunder
    
    // Returnera loggposten i det specificerade formatet
    return `[${timestamp}] Mottaget: ${msg}`;
}