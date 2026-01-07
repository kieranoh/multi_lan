package main

import (
	"fmt"
	"time"
)

/* Genera una entrada de registre per a un missatge d'usuari rebut amb la marca de temps actual, en el format '[<timestamp_iso_format>] Rebut: <msg>'.

@param msg El missatge d'usuari rebut.

@return L'entrada de registre per al missatge rebut. */
func generateReceiveLog(msg string) string {
	// Obtenir la marca de temps actual en format ISO 8601
	timestamp := time.Now().Format(time.RFC3339)
	
	// Construir l'entrada de registre en el format especificat
	logEntry := fmt.Sprintf("[%s] Rebut: %s", timestamp, msg)
	
	return logEntry
}