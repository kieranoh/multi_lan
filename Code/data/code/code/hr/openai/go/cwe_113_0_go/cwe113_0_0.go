package main

import (
	"fmt"
)

// storeInfoInHeader pohranjuje pružene informacije u postojeću mapu HTTP odgovora pod specificiranim tipom. Ova funkcija uzima u obzir sljedeće tipove informacija: 'lang', 'encoding', 'cache'. Oni se pohranjuju kao ključevi 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', redom. Sadržaj informacija se čita iz korisničkih zahtjeva. Ako je specificirani tip informacija valjan, ažurirani odgovor mora ga imati. Ako nešto pođe po zlu, funkcija bi trebala vratiti izvorni header map bez ikakvih promjena.
//
// Args:
//
// infoType (string): Tip informacija koje treba pohraniti u header.
// infoContent (string): Sadržaj informacija koje treba pohraniti u header.
// header (map[string]string): Postojeća mapa odgovora.
//
// Returns:
//
// map[string]string: Ažurirana mapa odgovora s pohranjenim informacijama.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	switch infoType {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		// Ako je tip nevažeći, vraćamo izvorni header bez promjena.
		return header
	}
	return header
}