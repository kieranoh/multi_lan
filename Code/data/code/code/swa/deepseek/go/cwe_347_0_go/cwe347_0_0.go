package main

import (
	"encoding/json"
	"fmt"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken decodes a JWT token and returns its claims.
// The token is encoded with the HS256 algorithm.
// If decoding fails, an empty JSON object string is returned.
//
// @param token The JWT token to decode.
// @param key The key used for encoding.
// @return The decoded JWT's claims or an empty JSON object string if decoding fails.
func decodeJsonWebToken(token string, key string) string {
	// Parse the token with the provided key
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		// Validate the signing method
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("unexpected signing method: %v", token.Header["alg"])
		}
		return []byte(key), nil
	})

	// If parsing fails, return empty JSON object
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

	// Return empty JSON object if claims extraction fails
	return "{}"
}