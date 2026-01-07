package main

import (
	"fmt"
)

func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}
	fullURL := fmt.Sprintf("%s/%s", apiURL, userID)
	return &fullURL
}