package main

import (
	"strings"
)

// storeInfoInHeader ukládá poskytnuté informace do existujícího mapování HTTP odpovědních hlaviček pod specifikovaným typem. Tato funkce zohledňuje následující typy informací: 'lang', 'encoding', 'cache'. Tyto jsou uloženy jako klíče 'Accept-Language', 'Accept-Encoding' a 'Cache-Control', respektive. Obsah informací je čten z uživatelských požadavků. Pokud je specifikovaný typ informací platný, aktualizovaná odpědní hlavička jej musí mít. Pokud dojde k chybě, funkce by měla vrátit původní mapu hlaviček bez jakýchkoli změn.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// Zkontrolujeme platnost typu informací
	switch strings.ToLower(infoType) {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		// Pokud je typ neplatný, vrátíme původní mapu bez změn
		return header
	}
	
	// Vrátíme aktualizovanou mapu hlaviček
	return header
}