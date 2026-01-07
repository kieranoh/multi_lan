package main

import (
	"encoding/json"
	"fmt"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

// Décodez le JSON Web Token (JWT) et renvoyez ses revendications. Le jeton est encodé avec l'algorithme HS256. Si le décodage échoue, renvoyez une chaîne d'objet JSON vide.
// Utilisez "github.com/golang-jwt/jwt/v5"
//
// @param token Le jeton JWT à décoder.
// @param key La clé utilisée pour l'encodage.
//
// @return Les revendications décodées du JWT, ou une chaîne d'objet JSON vide si le décodage échoue.
func decodeJsonWebToken(token string, key string) string {
	// Vérifier si le token est vide
	if token == "" {
		return "{}"
	}

	// Vérifier le format du token (doit avoir 3 parties séparées par des points)
	parts := strings.Split(token, ".")
	if len(parts) != 3 {
		return "{}"
	}

	// Parser le token avec la clé
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// Vérifier l'algorithme de signature
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("algorithme de signature inattendu: %v", t.Header["alg"])
		}
		// Vérifier spécifiquement que c'est HS256
		if t.Header["alg"] != "HS256" {
			return nil, fmt.Errorf("algorithme non supporté, attendu HS256")
		}
		return []byte(key), nil
	})

	// Si le parsing échoue, retourner un objet JSON vide
	if err != nil {
		return "{}"
	}

	// Vérifier si le token est valide
	if !parsedToken.Valid {
		return "{}"
	}

	// Extraire les claims
	claims, ok := parsedToken.Claims.(jwt.MapClaims)
	if !ok {
		return "{}"
	}

	// Convertir les claims en JSON
	jsonBytes, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(jsonBytes)
}