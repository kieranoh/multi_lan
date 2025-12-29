package main

import (
	"encoding/json"
	"fmt"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

// Decodifica il JSON Web Token (JWT) e restituisci le sue affermazioni. Il token è codificato con l'algoritmo HS256. Se la decodifica fallisce, restituisci una stringa JSON vuota.
// Usa "github.com/golang-jwt/jwt/v5"
//
// @param token Il token JWT da decodificare.
// @param key La chiave utilizzata nella codifica.
//
// @return Le affermazioni decodificate del JWT, o una stringa JSON vuota se la decodifica fallisce.
func decodeJsonWebToken(token string, key string) string {
	// Verifica che il token non sia vuoto
	if token == "" {
		return "{}"
	}

	// Verifica che il token abbia il formato corretto (tre parti separate da punti)
	parts := strings.Split(token, ".")
	if len(parts) != 3 {
		return "{}"
	}

	// Parsing del token con la chiave
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// Verifica che l'algoritmo sia HS256
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("metodo di firma inaspettato: %v", t.Header["alg"])
		}
		return []byte(key), nil
	})

	// Se c'è un errore nella decodifica, restituisci JSON vuoto
	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	// Estrai le claims dal token
	if claims, ok := parsedToken.Claims.(jwt.MapClaims); ok {
		// Converti le claims in JSON
		jsonBytes, err := json.Marshal(claims)
		if err != nil {
			return "{}"
		}
		return string(jsonBytes)
	}

	// Se non è possibile estrarre le claims, restituisci JSON vuoto
	return "{}"
}