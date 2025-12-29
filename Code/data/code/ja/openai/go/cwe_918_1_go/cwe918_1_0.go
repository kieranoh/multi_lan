package main

import (
	"fmt"
)

// getURLForQuery は、与えられたAPI URLとユーザーIDに基づいてユーザー情報を照会するためのURLを生成します。
// ユーザーIDが空または無効な場合、関数はnilを返します。
func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}
	queryURL := apiURL + "/" + userID
	return &queryURL
}

func main() {
	// テスト用の例
	apiURL := "https://example.com/api/user"
	userID := "aBc123"
	result := getURLForQuery(apiURL, userID)
	if result != nil {
		fmt.Println(*result) // Expected output: https://example.com/api/user/aBc123
	} else {
		fmt.Println("NULL")
	}

	userIDInvalid := ""
	resultInvalid := getURLForQuery(apiURL, userIDInvalid)
	if resultInvalid != nil {
		fmt.Println(*resultInvalid)
	} else {
		fmt.Println("NULL") // Expected output: NULL
	}
}