package main

import (
	"encoding/json"
	"fmt"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

// 解码 JSON Web Token (JWT) 并返回其声明。该令牌使用 HS256 算法编码。如果解码失败，返回一个空的 JSON 对象字符串。
// 使用 "github.com/golang-jwt/jwt/v5"
//
// @param token 要解码的 JWT 令牌。
// @param key 用于编码的密钥。
//
// @return 解码后的 JWT 声明，如果解码失败则返回一个空的 JSON 对象字符串。
func decodeJsonWebToken(token string, key string) string {
	// 如果令牌为空，直接返回空JSON对象
	if strings.TrimSpace(token) == "" {
		return "{}"
	}

	// 解析JWT令牌
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// 验证签名算法是否为HS256
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("unexpected signing method: %v", t.Header["alg"])
		}
		return []byte(key), nil
	})

	// 如果解析失败，返回空JSON对象
	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	// 提取声明
	claims, ok := parsedToken.Claims.(jwt.MapClaims)
	if !ok {
		return "{}"
	}

	// 将声明转换为JSON字符串
	jsonBytes, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(jsonBytes)
}