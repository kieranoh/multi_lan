package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken decodes a JSON Web Token (JWT) and returns its claims.
// The token is encoded using the HS256 algorithm. If decoding fails, it returns an empty JSON object string.
func decodeJsonWebToken(token string, key string) string {
	// Parse the token
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (any, error) {
		// Check that the signing method is what we expect
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorUnverified)
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		// Return empty JSON object on error
		return "{}"
	}

	// Get claims from the token
	claims, err := json.Marshal(parsedToken.Claims)
	if err != nil {
		// Return empty JSON object on error
		return "{}"
	}

	return string(claims)
}