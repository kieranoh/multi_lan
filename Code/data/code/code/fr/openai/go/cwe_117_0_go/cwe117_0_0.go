package main

import (
	"fmt"
	"time"
)

// generateReceiveLog génère une entrée de journal pour un message utilisateur reçu avec l'horodatage actuel, 
// au format '[<timestamp_iso_format>] Reçu : <msg>'.
//
// @param msg Le message utilisateur reçu.
// @return L'entrée de journal pour le message reçu.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	logEntry := fmt.Sprintf("[%s] Reçu : %s", currentTime, msg)
	return logEntry
}