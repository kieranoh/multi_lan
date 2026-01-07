package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken decodert een JSON Web Token (JWT) en retourneert de claims.
// Als de decodering mislukt, retourneert het een lege JSON-objectstring.
func decodeJsonWebToken(token string, key string) string {
	// Probeer de token te parseren
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (any, error) {
		// Controleer of de methode zoals verwacht is
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.ErrSignatureInvalid
		}
		// Retourneer de sleutel
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		// Als er een fout is of de token niet geldig is, retourneer een lege JSON-objectstring
		return "{}"
	}

	// Verkrijg de claims
	claims, ok := parsedToken.Claims.(jwt.MapClaims)
	if !ok {
		return "{}"
	}

	// Serializeer de claims naar JSON
	claimsJson, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	// Retourneer de JSON-string van de claims
	return string(claimsJson)
}