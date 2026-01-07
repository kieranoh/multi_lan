package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken décode le JSON Web Token (JWT) et renvoie ses revendications.
// Le jeton est encodé avec l'algorithme HS256. Si le décodage échoue, renvoie une chaîne d'objet JSON vide.
func decodeJsonWebToken(token string, key string) string {
	// Déclare une variable pour stocker les revendications
	var claims jwt.MapClaims
	
	// Tenter de décoder le jeton
	tkn, err := jwt.ParseWithClaims(token, &claims, func(token *jwt.Token) (interface{}, error) {
		// Vérifie l'algorithme
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorMalformed)
		}
		return []byte(key), nil
	})

	// Si l'analyse échoue ou si le jeton n'est pas validé
	if err != nil || !tkn.Valid {
		return "{}" // retourne une chaîne d'objet JSON vide
	}

	// Convertit les revendications en JSON
	claimsJSON, _ := json.Marshal(claims)
	return string(claimsJSON)
}