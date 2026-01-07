package main

import (
	"encoding/json"
	"fmt"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken decodes a JSON Web Token (JWT) and returns its claims.
// The token is encoded using the HS256 algorithm. If decoding fails, it returns an empty JSON object string.
func decodeJsonWebToken(token string, key string) string {
	// Parse the token
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		// Ensure the token's signing method is valid
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("unexpected signing method")
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		// If there is an error or the token is not valid, return an empty JSON object
		return "{}"
	}

	// Extract claims from the token
	claims, ok := parsedToken.Claims.(jwt.MapClaims)
	if !ok {
		return "{}"
	}

	// Convert claims to JSON
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(claimsJSON)
}