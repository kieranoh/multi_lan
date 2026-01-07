import (
	"strings"
)

func getURLForQuery(apiURL, userID string) *string {
	// Check if userID is empty or contains only whitespace
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	
	// Construct the URL by concatenating apiURL and userID with a "/" separator
	url := apiURL + "/" + userID
	
	return &url
}