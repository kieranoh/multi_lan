package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken dekodira JSON Web Token (JWT) i vraća njegove tvrdnje.
// Token je kodiran s HS256 algoritmom. Ako dekodiranje ne uspije, vraća prazan JSON objekt string.
func decodeJsonWebToken(token string, key string) string {
	claims := jwt.MapClaims{}
	tkn, err := jwt.ParseWithClaims(token, claims, func(t *jwt.Token) (interface{}, error) {
		// Provjeravamo da li je algoritam ispravan
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorInvalidSignature)
		}
		return []byte(key), nil
	})

	if err != nil || !tkn.Valid {
		return "{}"
	}

	// Konvertujemo tvrdnje u JSON objekt
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(claimsJSON)
}