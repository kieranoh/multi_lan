package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect provjerava je li navedeni URL cilja unutar zadanog domena. 
// Ako jest, vraća URL cilja za preusmjeravanje; inače, prebacuje se na URL domene za preusmjeravanje. 
// Koristi https protokol.
func getTargetForRedirect(target string, domain string) string {
	// Parsiranje ciljanog URL-a
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain // U slučaju greške, vraćamo domenski URL
	}

	// Provjera da li domena ciljanog URL-a sadrži zadanu domenu
	if strings.HasSuffix(parsedTarget.Host, domain) {
		return target // Vraćamo ciljani URL ako je unutar zadane domene
	}

	// Ako nije unutar zadane domene, vraćamo domenski URL
	return "https://" + domain
}