import (
	"strings"
)

func getURLForQuery(apiURL, userID string) *string {
	// Provjeri je li userID prazan ili nevažeći
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// Ukloni mogući završni kosu crtu iz apiURL-a
	cleanAPIURL := strings.TrimSuffix(apiURL, "/")
	
	// Generiraj URL
	result := cleanAPIURL + "/" + userID
	
	return &result
}