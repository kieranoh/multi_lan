package main

import (
	"encoding/json"
	"fmt"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

// Decodifica el JSON Web Token (JWT) i retorna les seves reclamacions. El token està codificat amb l'algorisme HS256. Si la decodificació falla, retorna una cadena d'objecte JSON buit.
// Utilitza "github.com/golang-jwt/jwt/v5"
//
// @param token El token JWT a decodificar.
// @param key La clau utilitzada en la codificació.
//
// @return Les reclamacions decodificades del JWT, o una cadena d'objecte JSON buit si la decodificació falla.
func decodeJsonWebToken(token string, key string) string {
	// Retorna un objecte JSON buit si el token està buit
	if strings.TrimSpace(token) == "" {
		return "{}"
	}

	// Parseja el token amb la clau
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// Verifica l'algorisme HS256
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("algorisme de signatura inesperat: %v", t.Header["alg"])
		}
		return []byte(key), nil
	})

	// Si hi ha un error en parsejar, retorna un objecte JSON buit
	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	// Extreu les reclamacions
	if claims, ok := parsedToken.Claims.(jwt.MapClaims); ok {
		// Converteix les reclamacions a JSON
		jsonBytes, err := json.Marshal(claims)
		if err != nil {
			return "{}"
		}
		return string(jsonBytes)
	}

	// Si no es poden extreure les reclamacions, retorna un objecte JSON buit
	return "{}"
}