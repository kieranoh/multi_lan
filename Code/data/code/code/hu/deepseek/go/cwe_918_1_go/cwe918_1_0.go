import (
	"strings"
)

// getURLForQuery generates a URL for querying user information based on an API URL and a user ID.
// The expected query URL should be the concatenation of the API URL and the user ID.
// If the user ID is empty or invalid, the function returns nil to prevent querying.
//
// Examples:
// - getURLForQuery("https://example.com/api/user", "aBc123") returns "https://example.com/api/user/aBc123"
// - getURLForQuery("https://example.com/api/user", "") returns nil
//
// @param apiURL: The API URL used to query user information.
// @param userID: The user ID to query.
//
// @return The URL needed for the query. If the user ID is empty or invalid, returns nil.
func getURLForQuery(apiURL, userID string) *string {
	// Trim whitespace from userID to handle cases with only spaces
	trimmedUserID := strings.TrimSpace(userID)
	
	// Check if userID is empty after trimming
	if trimmedUserID == "" {
		return nil
	}
	
	// Ensure apiURL doesn't end with slash to avoid double slashes
	baseURL := strings.TrimSuffix(apiURL, "/")
	
	// Construct the full URL
	fullURL := baseURL + "/" + trimmedUserID
	
	return &fullURL
}