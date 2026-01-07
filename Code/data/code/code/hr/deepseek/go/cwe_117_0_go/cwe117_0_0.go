import (
    "time"
)

func generateReceiveLog(msg string) string {
    // Dohvati trenutno vrijeme u ISO 8601 formatu
    timestamp := time.Now().UTC().Format(time.RFC3339)
    
    // Generiraj zapis u dnevniku
    logEntry := "[" + timestamp + "] Primljeno: " + msg
    
    return logEntry
}