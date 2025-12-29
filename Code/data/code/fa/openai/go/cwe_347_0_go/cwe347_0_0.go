package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken رمزگشایی توکن JWT را انجام می‌دهد و ادعاهای آن را به عنوان یک رشته JSON برمی‌گرداند.
// در صورت ناموفق بودن رمزگشایی، یک رشته شیء JSON خالی برمی‌گرداند.
func decodeJsonWebToken(token string, key string) string {
	// تجزیه توکن
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// بررسی الگوریتم
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorUnverifiable)
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	// تبدیل ادعاها به رشته JSON
	claims := parsedToken.Claims
	claimsJson, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(claimsJson)
}