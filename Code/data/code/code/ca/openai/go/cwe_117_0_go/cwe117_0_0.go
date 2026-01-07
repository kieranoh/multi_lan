package main

import (
	"fmt"
	"time"
)

// generateReceiveLog genera una entrada de registre per a un missatge d'usuari rebut amb la marca de temps actual,
// en el format '[<timestamp_iso_format>] Rebut: <msg>'.
//
// @param msg El missatge d'usuari rebut.
// @return L'entrada de registre per al missatge rebut.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	logEntry := fmt.Sprintf("[%s] Rebut: %s", currentTime, msg)
	return logEntry
}