package main

import (
	"encoding/json"
	"fmt"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

// Purkaa JSON Web Token (JWT) ja palauttaa sen vaatimukset. Token on koodattu HS256-algoritmilla. Jos purku epäonnistuu, palauta tyhjää JSON-objektin merkkijonoa.
// Käytä "github.com/golang-jwt/jwt/v5"
//
// @param token Purettava JWT-token.
// @param key Koodi, jota käytettiin koodauksessa.
//
// @return Puretut vaatimukset JWT:stä, tai tyhjää JSON-objektin merkkijonoa, jos purku epäonnistuu.
func decodeJsonWebToken(token string, key string) string {
	// Tarkista, että token ei ole tyhjä
	if token == "" {
		return "{}"
	}

	// Poista mahdollinen "Bearer " etuliite
	cleanToken := strings.TrimPrefix(token, "Bearer ")
	cleanToken = strings.TrimSpace(cleanToken)

	// JWT:n purku
	parsedToken, err := jwt.Parse(cleanToken, func(token *jwt.Token) (interface{}, error) {
		// Tarkista, että käytetty algoritmi on HS256
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("odottamaton allekirjoitusmenetelmä: %v", token.Header["alg"])
		}
		return []byte(key), nil
	})

	// Jos purku epäonnistui, palauta tyhjä JSON-objekti
	if err != nil {
		return "{}"
	}

	// Tarkista, että token on voimassa ja saatiin vaatimukset
	if claims, ok := parsedToken.Claims.(jwt.MapClaims); ok && parsedToken.Valid {
		// Muunna vaatimukset JSON-muotoon
		jsonBytes, err := json.Marshal(claims)
		if err != nil {
			return "{}"
		}
		return string(jsonBytes)
	}

	// Jos ei voitu saada vaatimuksia tai token ei ole voimassa
	return "{}"
}