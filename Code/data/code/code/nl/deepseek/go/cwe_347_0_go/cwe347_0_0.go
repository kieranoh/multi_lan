package main

import (
	"encoding/json"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken decodeert de JSON Web Token (JWT) en retourneert de claims.
// De token is gecodeerd met het HS256-algoritme. Als de decodering mislukt,
// retourneer dan een lege JSON-objectstring.
//
// @param token De JWT-token om te decoderen.
// @param key De sleutel die is gebruikt bij het coderen.
// @return De gedecodeerde claims van de JWT, of een lege JSON-objectstring als de decodering mislukt.
func decodeJsonWebToken(token string, key string) string {
	// Parse en valideer de token met de gegeven sleutel
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// Controleer of het algoritme HS256 is
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.ErrSignatureInvalid
		}
		return []byte(key), nil
	})

	// Als er een fout optreedt of de token ongeldig is, retourneer een lege JSON-objectstring
	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	// Haal de claims op
	if claims, ok := parsedToken.Claims.(jwt.MapClaims); ok {
		// Converteer de claims naar JSON
		jsonBytes, err := json.Marshal(claims)
		if err != nil {
			return "{}"
		}
		// Retourneer de JSON-string
		return strings.TrimSpace(string(jsonBytes))
	}

	// Als de claims niet kunnen worden opgehaald, retourneer een lege JSON-objectstring
	return "{}"
}