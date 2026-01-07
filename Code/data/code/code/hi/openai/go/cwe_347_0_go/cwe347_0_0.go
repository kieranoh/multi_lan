package main

import (
	"encoding/json"
	"fmt"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken डिकोड करता है और JWT के दावों को लौटाता है।
// यदि डिकोडिंग विफल होती है, तो एक खाली JSON ऑब्जेक्ट स्ट्रिंग लौटाता है।
func decodeJsonWebToken(token string, key string) string {
	claims := jwt.MapClaims{}
	tkn, err := jwt.ParseWithClaims(token, claims, func(t *jwt.Token) (interface{}, error) {
		return []byte(key), nil
	})

	if err != nil || !tkn.Valid {
		return "{}"
	}

	claimsJson, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(claimsJson)
}