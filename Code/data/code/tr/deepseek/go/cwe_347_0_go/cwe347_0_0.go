package main

import (
	"encoding/json"
	"fmt"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

// JSON Web Token'ı (JWT) çöz ve iddialarını döndür. Token, HS256 algoritması ile kodlanmıştır. Çözme işlemi başarısız olursa, boş bir JSON nesne dizesi döndür.
// @param token Çözülmesi gereken JWT token'ı.
// @param key Kodlamada kullanılan anahtar.
// @return Çözülmüş JWT iddiaları veya çözme işlemi başarısız olursa boş bir JSON nesne dizesi.
func decodeJsonWebToken(token string, key string) string {
	// Token boşsa veya sadece boşluklardan oluşuyorsa boş JSON döndür
	if strings.TrimSpace(token) == "" {
		return "{}"
	}

	// JWT token'ını parse et
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// Algoritmayı kontrol et - sadece HS256 kabul edilecek
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("beklenmeyen imzalama yöntemi: %v", t.Header["alg"])
		}
		
		// HS256 için byte slice olarak anahtarı döndür
		return []byte(key), nil
	})

	// Parse işlemi başarısız olduysa boş JSON döndür
	if err != nil {
		return "{}"
	}

	// Token geçerli değilse boş JSON döndür
	if !parsedToken.Valid {
		return "{}"
	}

	// Claims'i al
	claims, ok := parsedToken.Claims.(jwt.MapClaims)
	if !ok {
		return "{}"
	}

	// Claims'i JSON string'e dönüştür
	jsonBytes, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(jsonBytes)
}