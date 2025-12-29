package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken は、JSON Web Token (JWT) をデコードし、そのクレームを返します。
// トークンは HS256 アルゴリズムでエンコードされています。
// デコードに失敗した場合は、空の JSON オブジェクト文字列を返します。
// @param token デコードする JWT トークン。
// @param key エンコードに使用されるキー。
// @return デコードされた JWT のクレーム、またはデコードに失敗した場合は空の JSON オブジェクト文字列。
func decodeJsonWebToken(token string, key string) string {
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// HS256 のアルゴリズムを確認
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorSignatureInvalid)
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	claims := parsedToken.Claims
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(claimsJSON)
}