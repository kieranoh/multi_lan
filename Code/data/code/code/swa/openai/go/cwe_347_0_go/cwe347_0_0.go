package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken 디코드 JWT 토큰 na inreturn wa klamu zake. 
// Ikiwa kuna tatizo wakati wa decoding, inarejelea kituo cha JSON tupu.
func decodeJsonWebToken(token string, key string) string {
	// Kujaribu kuandika uwakilishi wa JWT
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (any, error) {
		// Thibitisha kuwa algorithimu iliyotumika ni HS256
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorMalformed)
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		// Ikiwa kuna makosa au token si halali, rudisha kituo cha JSON tupu
		return "{}"
	}

	// Pata klamu za JWT
	claims := parsedToken.Claims
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		// Ikiwa kuna makosa wakati wa kuandika JSON, rudisha kituo cha JSON tupu
		return "{}"
	}

	// Rudisha klamu kama kituo cha JSON
	return string(claimsJSON)
}