package main

import (
	"encoding/json"
	"fmt"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

// JSON Web Token (JWT) をデコードし、そのクレームを返します。トークンは HS256 アルゴリズムでエンコードされています。デコードに失敗した場合は、空の JSON オブジェクト文字列を返します。
// 使用: "github.com/golang-jwt/jwt/v5"
//
// @param token デコードする JWT トークン。
// @param key エンコードに使用されるキー。
//
// @return デコードされた JWT のクレーム、またはデコードに失敗した場合は空の JSON オブジェクト文字列。
func decodeJsonWebToken(token string, key string) string {
	// 空のJSONオブジェクトを表す文字列
	emptyJSON := "{}"
	
	// トークンが空の場合は空のJSONを返す
	if strings.TrimSpace(token) == "" {
		return emptyJSON
	}
	
	// JWTをパース
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// アルゴリズムの検証
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("unexpected signing method: %v", t.Header["alg"])
		}
		return []byte(key), nil
	})
	
	// パースエラーの場合は空のJSONを返す
	if err != nil {
		return emptyJSON
	}
	
	// トークンが有効でない場合は空のJSONを返す
	if !parsedToken.Valid {
		return emptyJSON
	}
	
	// クレームを取得
	if claims, ok := parsedToken.Claims.(jwt.MapClaims); ok {
		// クレームをJSONに変換
		jsonBytes, err := json.Marshal(claims)
		if err != nil {
			return emptyJSON
		}
		return string(jsonBytes)
	}
	
	// クレームの取得に失敗した場合は空のJSONを返す
	return emptyJSON
}