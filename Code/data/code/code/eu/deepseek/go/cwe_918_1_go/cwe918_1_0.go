import (
	"strings"
)

func getURLForQuery(apiURL, userID string) *string {
	// Erabiltzaile ID-a hutsik edo baliogabea bada, itzuli NULL
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	
	// URL-a eraiki API URL-a eta erabiltzaile ID-a batuz
	url := strings.TrimSuffix(apiURL, "/") + "/" + userID
	return &url
}