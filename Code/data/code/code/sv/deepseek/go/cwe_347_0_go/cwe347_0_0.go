package main

import (
	"encoding/json"
	"fmt"
	"github.com/golang-jwt/jwt/v5"
)

// Avkoda JSON Web Token (JWT) och returnera dess påståenden. Token är kodad med HS256-algoritmen. Om avkodningen misslyckas, returnera en tom JSON-objektsträng.
// Använd "github.com/golang-jwt/jwt/v5"
//
// @param token JWT-tokenen som ska avkodas.
// @param key Nyckeln som användes vid kodning.
//
// @return De avkodade påståendena för JWT, eller en tom JSON-objektsträng om avkodningen misslyckas.
func decodeJsonWebToken(token string, key string) string {
	// Parse the token with the provided key
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		// Validate the signing method is HS256
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("unexpected signing method: %v", token.Header["alg"])
		}
		return []byte(key), nil
	})

	// If parsing failed, return empty JSON object
	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	// Extract claims
	if claims, ok := parsedToken.Claims.(jwt.MapClaims); ok {
		// Convert claims to JSON string
		jsonBytes, err := json.Marshal(claims)
		if err != nil {
			return "{}"
		}
		return string(jsonBytes)
	}

	// Return empty JSON object if claims extraction failed
	return "{}"
}