package main

import (
    "fmt"
    "time"
)

/* Wygeneruj wpis dziennika dla odebranej wiadomości użytkownika z aktualnym znacznikiem czasu, w formacie '[<timestamp_iso_format>] Odebrano: <msg>'.

@param msg Odebrana wiadomość użytkownika.

@return Wpis dziennika dla odebranej wiadomości. */
func generateReceiveLog(msg string) string {
    // Pobierz aktualny czas w formacie ISO 8601
    timestamp := time.Now().Format(time.RFC3339)
    
    // Utwórz wpis dziennika w wymaganym formacie
    logEntry := fmt.Sprintf("[%s] Odebrano: %s", timestamp, msg)
    
    return logEntry
}