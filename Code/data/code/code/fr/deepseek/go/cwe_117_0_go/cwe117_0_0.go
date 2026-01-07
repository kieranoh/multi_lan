package main

import (
    "time"
)

// generateReceiveLog génère une entrée de journal pour un message utilisateur reçu avec l'horodatage actuel.
// Le format est '[<timestamp_iso_format>] Reçu : <msg>'
//
// @param msg Le message utilisateur reçu.
// @return L'entrée de journal pour le message reçu.
func generateReceiveLog(msg string) string {
    // Obtenir l'horodatage actuel au format ISO 8601
    timestamp := time.Now().Format(time.RFC3339)
    
    // Construire et retourner l'entrée de journal formatée
    return "[" + timestamp + "] Reçu : " + msg
}