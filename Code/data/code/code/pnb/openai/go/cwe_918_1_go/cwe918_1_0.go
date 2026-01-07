package main

import (
	"fmt"
)

func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}

	queryURL := apiURL + "/" + userID
	return &queryURL
}