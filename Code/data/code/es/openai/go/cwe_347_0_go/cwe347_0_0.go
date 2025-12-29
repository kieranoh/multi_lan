package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken decodifica el JSON Web Token (JWT) y devuelve sus reclamaciones.
// El token está codificado con el algoritmo HS256. Si la decodificación falla, devuelve una cadena de objeto JSON vacía.
func decodeJsonWebToken(token string, key string) string {
	claims := jwt.MapClaims{}
	tkn, err := jwt.ParseWithClaims(token, claims, func(token *jwt.Token) (interface{}, error) {
		return []byte(key), nil
	})

	if err != nil || !tkn.Valid {
		return "{}"
	}

	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(claimsJSON)
}