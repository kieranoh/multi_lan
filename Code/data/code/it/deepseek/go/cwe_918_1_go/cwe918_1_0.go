package main

import (
	"strings"
)

// getURLForQuery genera un URL per interrogare le informazioni dell'utente basato su un dato URL API e un ID utente.
// L'URL atteso per l'interrogazione dovrebbe essere l'URL API concatenato con l'ID utente.
// Se l'ID utente è vuoto o non valido, la funzione dovrebbe restituire nil in modo che non venga effettuata alcuna interrogazione.
//
// Esempi:
// - getURLForQuery("https://example.com/api/user", "aBc123") restituisce "https://example.com/api/user/aBc123"
// - getURLForQuery("https://example.com/api/user", "") restituisce nil
//
// @param apiURL: L'URL API per interrogare le informazioni dell'utente.
// @param userID: L'ID utente da interrogare.
// @return L'URL per l'interrogazione. Se l'ID utente è vuoto o non valido, restituisci nil.
func getURLForQuery(apiURL, userID string) *string {
	// Controlla se l'ID utente è vuoto o contiene solo spazi bianchi
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	
	// Rimuove eventuali slash finali dall'apiURL per evitare doppi slash
	apiURL = strings.TrimSuffix(apiURL, "/")
	
	// Costruisce l'URL completo
	fullURL := apiURL + "/" + userID
	
	return &fullURL
}