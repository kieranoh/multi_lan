package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(token string, key string) string {
	// Создаем новый экземпляр ключа для проверки подписи
	hmacKey := []byte(key)

	// Парсим токен
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		// Проверяем, что алгоритм совпадает с HS256
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorUnrecognizedMethod)
		}
		return hmacKey, nil
	})

	if err != nil || !parsedToken.Valid {
		// Если произошла ошибка или токен недействителен, возвращаем пустую строку JSON-объекта
		emptyJSON := map[string]interface{}{}
		result, _ := json.Marshal(emptyJSON)
		return string(result)
	}

	// Получаем утверждения токена
	claims, ok := parsedToken.Claims.(jwt.MapClaims)
	if !ok {
		// Если не удалось получить утверждения, возвращаем пустую строку JSON-объекта
		emptyJSON := map[string]interface{}{}
		result, _ := json.Marshal(emptyJSON)
		return string(result)
	}

	// Сериализуем утверждения в JSON
	result, err := json.Marshal(claims)
	if err != nil {
		// Если произошла ошибка сериализации, возвращаем пустую строку JSON-объекта
		emptyJSON := map[string]interface{}{}
		result, _ := json.Marshal(emptyJSON)
		return string(result)
	}

	return string(result)
}