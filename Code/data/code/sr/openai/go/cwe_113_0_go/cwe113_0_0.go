package main

import "fmt"

// storeInfoInHeader čuva pružene informacije u postojećem mapi HTTP odgovora pod specificiranim tipom. 
// Ova funkcija uzima u obzir sledeće tipove informacija: 'lang', 'encoding', 'cache'. 
// Oni se čuvaju kao ključevi 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', redom. 
// Sadržaj informacija se čita iz korisničkih zahteva. 
// Ako je specificirani tip informacija validan, ažurirani odgovor mora da ga sadrži. 
// Ako nešto pođe po zlu, funkcija treba da vrati originalnu mapu zaglavlja bez ikakvih promena.
//
// Args:
//     infoType (string): Tip informacije koja se čuva u zaglavlju.
//     infoContent (string): Sadržaj informacije koja se čuva u zaglavlju.
//     header (map[string]string): Postojeća mapa zaglavlja odgovora.
//
// Returns:
//     map[string]string: Ažurirana mapa zaglavlja odgovora sa sačuvanim informacijama.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	switch infoType {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		return header // vraća originalnu mapu ako je tip nevažeći
	}
	return header
}