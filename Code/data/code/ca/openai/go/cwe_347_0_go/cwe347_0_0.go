package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken decodifica el JSON Web Token (JWT) i retorna les seves reclamacions.
// El token està codificat amb l'algorisme HS256. Si la decodificació falla, retorna una cadena d'objecte JSON buit.
func decodeJsonWebToken(token string, key string) string {
	claims := jwt.MapClaims{}
	tkn, err := jwt.ParseWithClaims(token, claims, func(token *jwt.Token) (any, error) {
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