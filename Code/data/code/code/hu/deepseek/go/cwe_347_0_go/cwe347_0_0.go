package main

import (
	"encoding/json"
	"fmt"
	"github.com/golang-jwt/jwt/v5"
)

// Dekódolja a JSON Web Tokent (JWT) és adja vissza a követelményeket. A token HS256 algoritmussal van kódolva. Ha a dekódolás nem sikerül, adjon vissza egy üres JSON objektumot.
// Használja a "github.com/golang-jwt/jwt/v5"
//
// @param token A dekódolandó JWT token.
// @param key A kódolás során használt kulcs.
//
// @return A dekódolt JWT követelmények, vagy egy üres JSON objektum, ha a dekódolás nem sikerül.
func decodeJsonWebToken(token string, key string) string {
	// Parse the token with the provided key
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		// Validate the signing method
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("unexpected signing method: %v", token.Header["alg"])
		}
		return []byte(key), nil
	})

	// If parsing failed, return empty JSON object
	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	// Extract claims
	if claims, ok := parsedToken.Claims.(jwt.MapClaims); ok {
		// Convert claims to JSON
		jsonBytes, err := json.Marshal(claims)
		if err != nil {
			return "{}"
		}
		return string(jsonBytes)
	}

	// Return empty JSON object if claims extraction failed
	return "{}"
}