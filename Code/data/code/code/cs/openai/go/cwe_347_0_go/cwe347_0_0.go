package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(token string, key string) string {
	// Dekódujte token
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// Ověřte, že algoritmus je HS256
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.ErrInvalidKey
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		// V případě chyby nebo neplatného tokenu vraťte prázdný JSON objekt
		return "{}"
	}

	// Získejte nároky z tokenu
	claims := parsedToken.Claims

	// Převod nároků na JSON
	claimsJSON, _ := json.Marshal(claims)

	return string(claimsJSON)
}