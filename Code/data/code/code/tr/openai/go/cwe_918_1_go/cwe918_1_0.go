package main

import (
	"fmt"
)

// getURLForQuery oluşturulacak sorgu URL'sini döndürür. Eğer kullanıcı kimliği boş veya geçersizse, NULL döner.
func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}
	fullURL := fmt.Sprintf("%s/%s", apiURL, userID)
	return &fullURL
}