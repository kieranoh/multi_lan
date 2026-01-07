import (
    "time"
)

/* Genereer een logboekvermelding voor een ontvangen gebruikersbericht met de huidige tijdstempel, in het formaat '[<timestamp_iso_format>] Ontvangen: <msg>'.

@param msg Het ontvangen gebruikersbericht.

@return De logboekvermelding voor het ontvangen bericht. */
func generateReceiveLog(msg string) string {
    // Haal de huidige tijd op in UTC en formatteer naar ISO 8601 formaat
    timestamp := time.Now().UTC().Format(time.RFC3339)
    
    // Construeer de logboekvermelding volgens het gespecificeerde formaat
    logEntry := "[" + timestamp + "] Ontvangen: " + msg
    
    return logEntry
}