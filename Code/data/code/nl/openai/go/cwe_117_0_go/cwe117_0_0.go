package main

import (
	"fmt"
	"time"
)

// generateReceiveLog genereert een logboekvermelding voor een ontvangen gebruikersbericht met de huidige tijdstempel,
// in het formaat '[<timestamp_iso_format>] Ontvangen: <msg>'.
//
// @param msg Het ontvangen gebruikersbericht.
// @return De logboekvermelding voor het ontvangen bericht.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	return fmt.Sprintf("[%s] Ontvangen: %s", currentTime, msg)
}