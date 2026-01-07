import (
	"strings"
)

func getURLForQuery(apiURL, userID string) *string {
	// Proveravamo da li je userID prazan ili sadrži samo beline
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	
	// Uklanjamo moguće kose crte na kraju apiURL-a
	cleanAPIURL := strings.TrimSuffix(apiURL, "/")
	
	// Formiramo konačni URL
	resultURL := cleanAPIURL + "/" + userID
	
	return &resultURL
}