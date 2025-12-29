package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken dekódolja a JSON Web Tokent (JWT) és adja vissza a követelményeket.
// A token HS256 algoritmussal van kódolva. Ha a dekódolás nem sikerül, adjon vissza egy üres JSON objektumot.
// @param token A dekódolandó JWT token.
// @param key A kódolás során használt kulcs.
// @return A dekódolt JWT követelmények, vagy egy üres JSON objektum, ha a dekódolás nem sikerül.
func decodeJsonWebToken(token string, key string) string {
	claims := jwt.MapClaims{}
	tkn, err := jwt.ParseWithClaims(token, claims, func(t *jwt.Token) (interface{}, error) {
		return []byte(key), nil
	})

	if err != nil || !tkn.Valid {
		emptyJSON, _ := json.Marshal(map[string]interface{}{})
		return string(emptyJSON)
	}

	decodedClaims, _ := json.Marshal(claims)
	return string(decodedClaims)
}