package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken avkodar JSON Web Token (JWT) och returnerar dess påståenden.
// Token är kodad med HS256-algoritmen. Om avkodningen misslyckas, returnera en tom JSON-objektsträng.
func decodeJsonWebToken(token string, key string) string {
	// Skapa en ny variabel av typen jwt.Token för att hålla den avkodade token
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		// Kontrollera att token är signerat med HS256 algoritmen
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.ErrSignatureInvalid
		}
		// Återvänd nyckeln som användes för att signera token
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		// Om avkodning misslyckas, returnera en tom JSON-objektsträng
		return "{}"
	}

	// Hämta påståendena (claims) från den avkodade token
	claims := parsedToken.Claims

	// Konvertera påståendena till JSON-format
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		// Om konverteringen misslyckas, returnera en tom JSON-objektsträng
		return "{}"
	}

	// Returnera de avkodade påståendena som en JSON-sträng
	return string(claimsJSON)
}