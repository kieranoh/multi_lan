import (
	"strings"
)

func getURLForQuery(apiURL, userID string) *string {
	// Überprüfe, ob die Benutzer-ID leer oder ungültig ist
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// Entferne führende und abschließende Schrägstriche von der API-URL für konsistente Verkettung
	baseURL := strings.TrimRight(apiURL, "/")
	
	// Erstelle die vollständige URL
	fullURL := baseURL + "/" + userID
	
	return &fullURL
}