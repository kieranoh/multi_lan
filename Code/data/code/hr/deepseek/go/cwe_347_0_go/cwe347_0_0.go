import (
	"encoding/json"
	"fmt"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(tokenString string, key string) string {
	// Prazan token treba vratiti prazan JSON objekt
	if strings.TrimSpace(tokenString) == "" {
		return "{}"
	}

	// Parsiraj token s HS256 algoritmom
	token, err := jwt.Parse(tokenString, func(token *jwt.Token) (interface{}, error) {
		// Provjeri je li algoritam HS256
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("neočekivani algoritam potpisivanja: %v", token.Header["alg"])
		}
		return []byte(key), nil
	})

	// Ako je došlo do greške pri parsiranju, vrati prazan JSON objekt
	if err != nil {
		return "{}"
	}

	// Ako token nije valjan, vrati prazan JSON objekt
	if !token.Valid {
		return "{}"
	}

	// Dohvati tvrdnje (claims)
	claims, ok := token.Claims.(jwt.MapClaims)
	if !ok {
		return "{}"
	}

	// Konvertiraj tvrdnje u JSON string
	jsonBytes, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(jsonBytes)
}