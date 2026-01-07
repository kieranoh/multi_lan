package main

import (
    "encoding/json"
    "strings"

    "github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(tokenStr string, key string) string {
    // Parse o token com a chave fornecida
    token, err := jwt.Parse(tokenStr, func(token *jwt.Token) (interface{}, error) {
        // Verificar se o algoritmo é HS256
        if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
            return nil, jwt.ErrSignatureInvalid
        }
        return []byte(key), nil
    })

    // Se houver erro na análise, retorne objeto JSON vazio
    if err != nil || !token.Valid {
        return "{}"
    }

    // Extrair as reivindicações
    if claims, ok := token.Claims.(jwt.MapClaims); ok {
        // Converter claims para JSON
        jsonBytes, err := json.Marshal(claims)
        if err != nil {
            return "{}"
        }
        return string(jsonBytes)
    }

    return "{}"
}