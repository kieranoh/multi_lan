package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken dekodira JSON Web Token (JWT) i vraća njegove tvrdnje.
// Token je kodiran sa HS256 algoritmom. Ako dekodiranje ne uspe, vraća prazan JSON objekat kao string.
func decodeJsonWebToken(token string, key string) string {
	type Claims struct {
		// Definišite strukturu tvrdnji ovde prema očekivanim podacima u JWT-u
		jwt.RegisteredClaims
	}

	// Dekodiranje JWT-a
	parsedToken, err := jwt.ParseWithClaims(token, &Claims{}, func(token *jwt.Token) (any, error) {
		// Proverite da li je algoritam ispravan
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.ErrInvalidSigningMethod
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		// U slučaju greške ili nevažećeg tokena, vraćamo prazan JSON objekat
		return "{}"
	}

	claims, ok := parsedToken.Claims.(*Claims)
	if !ok {
		return "{}"
	}

	// Konvertovanje tvrdnji u JSON
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(claimsJSON)
}