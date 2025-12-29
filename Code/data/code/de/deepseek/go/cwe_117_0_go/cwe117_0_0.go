import (
    "time"
)

/* Erzeuge einen Protokolleintrag für eine empfangene Benutzer Nachricht mit dem aktuellen Zeitstempel im Format '[<timestamp_iso_format>] Empfangen: <msg>'.

@param msg Die empfangene Benutzer Nachricht.

@return Der Protokolleintrag für die empfangene Nachricht. */
func generateReceiveLog(msg string) string {
    // ISO 8601 format: "2006-01-02T15:04:05Z07:00"
    timestamp := time.Now().Format(time.RFC3339)
    return "[" + timestamp + "] Empfangen: " + msg
}