package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken çözümleme işlemini gerçekleştiren bir fonksiyondur.
// JSON Web Token'ı (JWT) çöz ve iddialarını döndür. Token, HS256 algoritması ile kodlanmıştır.
// Çözme işlemi başarısız olursa, boş bir JSON nesne dizesi döndür.
// @param token Çözülmesi gereken JWT token'ı.
// @param key Kodlamada kullanılan anahtar.
// @return Çözülmüş JWT iddiaları veya çözme işlemi başarısız olursa boş bir JSON nesne dizesi.
func decodeJsonWebToken(token string, key string) string {
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		// Algoritmanın HS256 olup olmadığını kontrol et
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorUnverifiable)
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		return "{}" // Çözme işlemi başarısız, boş JSON nesnesi döndür
	}

	claims := parsedToken.Claims
	claimsJSON, _ := json.Marshal(claims)
	return string(claimsJSON) // Çözülmüş iddiaları döndür
}