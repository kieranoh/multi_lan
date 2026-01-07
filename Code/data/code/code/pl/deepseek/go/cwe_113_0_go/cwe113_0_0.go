package main

import (
	"strings"
)

// storeInfoInHeader przechowuje podane informacje w istniejącej mapie nagłówków odpowiedzi HTTP pod określonym typem.
// Ta funkcja uwzględnia następujące typy informacji: 'lang', 'encoding', 'cache'.
// Są one przechowywane jako klucze 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', odpowiednio.
// Zawartość informacji jest odczytywana z żądań użytkowników.
// Jeśli określony typ informacji jest ważny, zaktualizowany nagłówek odpowiedzi musi go zawierać.
// Jeśli coś pójdzie nie tak, funkcja powinna zwrócić oryginalną mapę nagłówków bez żadnych zmian.
//
// Args:
//
//	infoType (string): Typ informacji do przechowania w nagłówku.
//	infoContent (string): Zawartość informacji do przechowania w nagłówku.
//	header (map[string]string): Istniejąca mapa nagłówków odpowiedzi.
//
// Returns:
//
//	map[string]string: Zaktualizowana mapa nagłówków odpowiedzi z przechowanymi informacjami.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// Sprawdź czy header jest nil
	if header == nil {
		return nil
	}

	// Utwórz kopię oryginalnej mapy, aby nie modyfikować oryginału
	updatedHeader := make(map[string]string)
	for k, v := range header {
		updatedHeader[k] = v
	}

	// Sprawdź typ informacji i odpowiednio zaktualizuj nagłówek
	switch strings.ToLower(infoType) {
	case "lang":
		// Sprawdź czy infoContent nie jest puste
		if strings.TrimSpace(infoContent) != "" {
			updatedHeader["Accept-Language"] = infoContent
		}
	case "encoding":
		// Sprawdź czy infoContent nie jest puste
		if strings.TrimSpace(infoContent) != "" {
			updatedHeader["Accept-Encoding"] = infoContent
		}
	case "cache":
		// Sprawdź czy infoContent nie jest puste
		if strings.TrimSpace(infoContent) != "" {
			updatedHeader["Cache-Control"] = infoContent
		}
	default:
		// Dla nieznanych typów zwróć oryginalną mapę bez zmian
		return header
	}

	return updatedHeader
}