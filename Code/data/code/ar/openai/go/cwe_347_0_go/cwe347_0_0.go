package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken يقوم بفك تشفير رمز الويب JSON (JWT) وأعاد المطالبات الخاصة به.
// يتم ترميز الرمز باستخدام خوارزمية HS256. إذا فشل فك التشفير، يعيد سلسلة كائن JSON فارغة.
func decodeJsonWebToken(token string, key string) string {
	// إعداد المفتاح للتوقيع
	hmacSecret := []byte(key)

	// محاولة فك تشفير الرمز
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		// التأكد من أن طريقة التوقيع هي HS256
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorSignatureInvalid)
		}
		return hmacSecret, nil
	})

	if err != nil || !parsedToken.Valid {
		// إذا فشل فك التشفير، نعيد سلسلة كائن JSON فارغة
		return "{}"
	}

	// الحصول على المطالبات
	claims := parsedToken.Claims.(jwt.MapClaims)

	// تحويل المطالبات إلى سلسلة JSON
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		// إذا حدث خطأ أثناء التحويل، نعيد سلسلة كائن JSON فارغة
		return "{}"
	}

	return string(claimsJSON)
}