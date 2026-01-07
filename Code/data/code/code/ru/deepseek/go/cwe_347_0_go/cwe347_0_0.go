package main

import (
	"encoding/json"
	"fmt"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(tokenStr string, keyStr string) string {
	// Проверяем, что токен не пустой
	if tokenStr == "" {
		return "{}"
	}

	// Проверяем формат токена (должен содержать 3 части, разделенные точками)
	parts := strings.Split(tokenStr, ".")
	if len(parts) != 3 {
		return "{}"
	}

	// Создаем парсер с методом проверки подписи HS256
	parser := jwt.NewParser(jwt.WithValidMethods([]string{jwt.SigningMethodHS256.Name}))

	// Парсим токен с использованием ключа
	token, err := parser.Parse(tokenStr, func(token *jwt.Token) (interface{}, error) {
		// Проверяем, что используется ожидаемый алгоритм подписи
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("неожиданный алгоритм подписи: %v", token.Header["alg"])
		}
		return []byte(keyStr), nil
	})

	// Если произошла ошибка при парсинге, возвращаем пустой JSON-объект
	if err != nil {
		return "{}"
	}

	// Проверяем, что токен валиден
	if !token.Valid {
		return "{}"
	}

	// Извлекаем утверждения (claims)
	claims, ok := token.Claims.(jwt.MapClaims)
	if !ok {
		return "{}"
	}

	// Конвертируем claims в JSON строку
	jsonBytes, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(jsonBytes)
}