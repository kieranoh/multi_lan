package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken decodes the JSON Web Token (JWT) and returns its claims.
// The token is encoded with the HS256 algorithm. If decoding fails, it returns an empty JSON object string.
func decodeJsonWebToken(token string, key string) string {
	claims := jwt.MapClaims{}
	tkn, err := jwt.ParseWithClaims(token, claims, func(t *jwt.Token) (any, error) {
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorSignatureInvalid)
		}
		return []byte(key), nil
	})

	if err != nil || !tkn.Valid {
		return "{}"
	}

	decodedClaims, _ := json.Marshal(claims)
	return string(decodedClaims)
}