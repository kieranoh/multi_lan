package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken decodes a JSON Web Token (JWT) and returns its claims.
// The token is encoded using the HS256 algorithm. If decoding fails, an empty JSON object string is returned.
// @param token: The JWT token to decode.
// @param key: The key used for encoding.
// @return: The claims of the decoded JWT or an empty JSON object string in case of failure.
func decodeJsonWebToken(token string, key string) string {
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		// Ensure the token method is HMAC
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorUnverifiable)
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	claims := parsedToken.Claims.(jwt.MapClaims)
	claimsJson, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}
	return string(claimsJson)
}