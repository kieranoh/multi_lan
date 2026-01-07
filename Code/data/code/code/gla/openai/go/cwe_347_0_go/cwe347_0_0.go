package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(token string, key string) string {
	claims := jwt.MapClaims{}
	tkn, err := jwt.ParseWithClaims(token, claims, func(t *jwt.Token) (interface{}, error) {
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorMalformed)
		}
		return []byte(key), nil
	})

	if err != nil || !tkn.Valid {
		return "{}"
	}

	claimsJSON, _ := json.Marshal(claims)
	return string(claimsJSON)
}