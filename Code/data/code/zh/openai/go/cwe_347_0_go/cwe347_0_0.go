package main

import (
	"encoding/json"
	"log"

	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken 解码 JSON Web Token (JWT) 并返回其声明。
// 该令牌使用 HS256 算法编码。如果解码失败，返回一个空的 JSON 对象字符串。
// @param token 要解码的 JWT 令牌。
// @param key 用于编码的密钥。
// @return 解码后的 JWT 声明，如果解码失败则返回一个空的 JSON 对象字符串。
func decodeJsonWebToken(token string, key string) string {
	// 创建一个空的 map 来存储声明
	claims := jwt.MapClaims{}

	// 解析 JWT
	parsedToken, err := jwt.ParseWithClaims(token, claims, func(token *jwt.Token) (interface{}, error) {
		// 确保算法是 HS256
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorUnverifiable)
		}
		return []byte(key), nil
	})

	// 如果解析失败，返回空的 JSON 对象字符串
	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	// 将 claims 转换为 JSON 字符串
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		log.Println("Error marshaling claims to JSON:", err)
		return "{}"
	}

	return string(claimsJSON)
}