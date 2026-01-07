package main

import (
	"encoding/json"
	"fmt"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken decodes a JWT token and returns its claims.
// The token is encoded with HS256 algorithm. If decoding fails,
// an empty JSON object string is returned.
//
// @param token JWT token to decode
// @param key key used for encoding
// @return decoded JWT claims or empty JSON object string if decoding fails
func decodeJsonWebToken(token string, key string) string {
	// Parse the token with the provided key
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
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

	// Check if token is valid and get claims
	if claims, ok := parsedToken.Claims.(jwt.MapClaims); ok && parsedToken.Valid {
		// Convert claims to JSON string
		jsonBytes, err := json.Marshal(claims)
		if err != nil {
			// If JSON marshaling fails, return empty JSON object
			return "{}"
		}
		return string(jsonBytes)
	}

	// Token is invalid
	return "{}"
}