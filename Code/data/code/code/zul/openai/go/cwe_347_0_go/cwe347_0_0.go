package main

import (
	"encoding/json"
	"fmt"

	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken decodes a JSON web token (JWT) and returns its claims.
// The token is encoded using the HS256 algorithm. If decoding fails,
// it returns an empty JSON object string.
//
// @param token The JWT token to decode.
// @param key The key used for encoding.
//
// @return The claims of the decoded JWT or an empty JSON object string in case of failure.
func decodeJsonWebToken(token string, key string) string {
	// Parse the token
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		// Check if the signing method is HMAC
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("unexpected signing method: %v", token.Header["alg"])
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		// Return an empty JSON object if decoding fails
		return "{}"
	}

	// Extract claims and convert to JSON
	claims := parsedToken.Claims
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		// Return an empty JSON object in case of marshaling error
		return "{}"
	}

	return string(claimsJSON)
}