import (
    "time"
    "fmt"
)

// generateReceiveLog erabiltzailearen mezu bat jaso den log irteera sortzen du,
// formatuan '[<timestamp_iso_format>] Jasotakoa: <msg>'.
//
// @param msg Jasotako erabiltzaile mezu.
// @return Jasotako mezuaren log irteera.
func generateReceiveLog(msg string) string {
    // ISO 8601 formatua lortu (Go-ren RFC3339 formatua erabiliz)
    timestamp := time.Now().Format(time.RFC3339)
    
    // Log irteera formatua sortu
    logEntry := fmt.Sprintf("[%s] Jasotakoa: %s", timestamp, msg)
    
    return logEntry
}