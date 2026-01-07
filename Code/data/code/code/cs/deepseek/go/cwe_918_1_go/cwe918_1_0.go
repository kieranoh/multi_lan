import (
	"strings"
)

func getURLForQuery(apiURL, userID string) *string {
	// Kontrola, zda je userID prázdný nebo neplatný
	if userID == "" || strings.TrimSpace(userID) == "" {
		return nil
	}

	// Sestavení URL s userID
	// Odstranění případných koncových lomítek z apiURL
	cleanAPIURL := strings.TrimRight(apiURL, "/")
	resultURL := cleanAPIURL + "/" + userID

	return &resultURL
}