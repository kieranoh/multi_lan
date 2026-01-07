import (
	"strings"
)

func getURLForQuery(apiURL, userID string) *string {
    // Controleer of de gebruikers-ID leeg of ongeldig is
    if userID == "" || strings.TrimSpace(userID) == "" {
        return nil
    }
    
    // Genereer de URL door de gebruikers-ID aan de API-URL toe te voegen
    url := apiURL + "/" + userID
    
    // Retourneer een pointer naar de gegenereerde URL
    return &url
}