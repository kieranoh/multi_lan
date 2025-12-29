package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken purkaa JSON Web Token (JWT) ja palauttaa sen vaatimukset.
// Token on koodattu HS256-algoritmilla. Jos purku epäonnistuu, palauttaa tyhjää JSON-objektin merkkijonoa.
//
// @param token Purettava JWT-token.
// @param key Koodi, jota käytettiin koodauksessa.
//
// @return Puretut vaatimukset JWT:stä, tai tyhjää JSON-objektin merkkijonoa, jos purku epäonnistuu.
func decodeJsonWebToken(token string, key string) string {
	// Yritetään purkaa JWT
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		// Varmistetaan, että käytetty algoritmi on HS256
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("invalid signing method", jwt.ValidationErrorSignatureInvalid)
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		// Jos purku epäonnistuu, palautetaan tyhjää JSON-objektin merkkijonoa
		return "{}"
	}

	// Puretaan vaatimukset
	claims, ok := parsedToken.Claims.(jwt.MapClaims)
	if !ok {
		return "{}"
	}

	// Muutetaan vaatimukset JSON-merkkijonoksi
	claimsJSON, _ := json.Marshal(claims)
	return string(claimsJSON)
}