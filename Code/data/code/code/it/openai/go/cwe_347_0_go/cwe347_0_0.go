package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken decodifica il JSON Web Token (JWT) e restituisce le sue affermazioni.
// Il token è codificato con l'algoritmo HS256. Se la decodifica fallisce, restituisce una stringa JSON vuota.
// @param token Il token JWT da decodificare.
// @param key La chiave utilizzata nella codifica.
// @return Le affermazioni decodificate del JWT, o una stringa JSON vuota se la decodifica fallisce.
func decodeJsonWebToken(token string, key string) string {
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorUnverifiable)
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	claims := parsedToken.Claims
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(claimsJSON)
}