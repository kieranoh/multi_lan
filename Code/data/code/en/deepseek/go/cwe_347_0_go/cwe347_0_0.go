import (
	"encoding/json"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(token string, key string) string {
	// Parse the token with the provided key
	t, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// Validate the signing method
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.ErrSignatureInvalid
		}
		return []byte(key), nil
	})

	// If parsing fails, return empty JSON object
	if err != nil || !t.Valid {
		return "{}"
	}

	// Extract claims
	claims, ok := t.Claims.(jwt.MapClaims)
	if !ok {
		return "{}"
	}

	// Convert claims to JSON string
	jsonBytes, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(jsonBytes)
}