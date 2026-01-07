package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken Deskodifikatu JSON Web Token (JWT) eta itzuli bere aldakuntzak. 
// Tokena HS256 algoritmoarekin kodificatuta dago. Deskodifikazioa huts egiten badu, 
// itzuli JSON objektu huts baten stringa.
// @param token Deskodifikatu beharreko JWT tokena.
// @param key Kodifikazioan erabilitako gakoa.
// @return JWTren deskodifikatutako aldakuntzak, edo JSON objektu huts baten stringa
func decodeJsonWebToken(token string, key string) string {
	// Aldakuntza bat sortu JWT deskodifikatu ondoren itzultzeko
	var claims jwt.MapClaims

	// Tokena deskodifikatu eta egiaztatu
	tkn, err := jwt.ParseWithClaims(token, &claims, func(token *jwt.Token) (interface{}, error) {
		return []byte(key), nil
	})

	if err != nil || !tkn.Valid {
		// Deskodifikazioa huts egin du, JSON objektu huts baten stringa itzuli
		return "{}"
	}

	// Aldakuntzak JSON formatuan itzuli
	result, _ := json.Marshal(claims)
	return string(result)
}