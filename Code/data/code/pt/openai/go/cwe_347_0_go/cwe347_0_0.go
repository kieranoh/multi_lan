package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken decodifica o JSON Web Token (JWT) e retorna suas reivindicações.
// Se a decodificação falhar, retorna uma string de objeto JSON vazia.
func decodeJsonWebToken(token string, key string) string {
	claims := jwt.MapClaims{}
	parsedToken, err := jwt.ParseWithClaims(token, claims, func(token *jwt.Token) (any, error) {
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.ErrSignatureInvalid
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(claimsJSON)
}