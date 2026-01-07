package main

// storeInfoInHeader przechowuje podane informacje w istniejącej mapie nagłówków odpowiedzi HTTP pod określonym typem.
// Ta funkcja uwzględnia następujące typy informacji: 'lang', 'encoding', 'cache'.
// Są one przechowywane jako klucze 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', odpowiednio.
// Zawartość informacji jest odczytywana z żądań użytkowników.
// Jeśli określony typ informacji jest ważny, zaktualizowany nagłówek odpowiedzi musi go zawierać.
// Jeśli coś pójdzie nie tak, funkcja powinna zwrócić oryginalną mapę nagłówków bez żadnych zmian.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	switch infoType {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		// Jeśli typ informacji nie jest ważny, zwracamy oryginalną mapę nagłówków.
		return header
	}
	return header
}