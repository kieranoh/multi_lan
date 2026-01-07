package main

import (
	"encoding/json"
	"fmt"
	"github.com/golang-jwt/jwt/v5"
)

// Zdekoduj token JSON Web Token (JWT) i zwróć jego roszczenia. Token jest zakodowany algorytmem HS256. Jeśli dekodowanie się nie powiedzie, zwróć pusty ciąg obiektu JSON.
// Użyj "github.com/golang-jwt/jwt/v5"
//
// @param token Token JWT do zdekodowania.
// @param key Klucz użyty do kodowania.
//
// @return Zdekodowane roszczenia JWT lub pusty ciąg obiektu JSON, jeśli dekodowanie się nie powiedzie.
func decodeJsonWebToken(tokenStr string, key string) string {
	// Parse the token with the provided key
	token, err := jwt.Parse(tokenStr, func(token *jwt.Token) (interface{}, error) {
		// Validate the signing method
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("unexpected signing method: %v", token.Header["alg"])
		}
		return []byte(key), nil
	})

	// If parsing failed, return empty JSON object
	if err != nil {
		return "{}"
	}

	// Check if token is valid
	if claims, ok := token.Claims.(jwt.MapClaims); ok && token.Valid {
		// Convert claims to JSON string
		jsonBytes, err := json.Marshal(claims)
		if err != nil {
			return "{}"
		}
		return string(jsonBytes)
	}

	// Return empty JSON object if token is invalid
	return "{}"
}