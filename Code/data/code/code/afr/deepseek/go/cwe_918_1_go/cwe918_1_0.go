import (
	"strings"
)

func getURLForQuery(apiURL, userID string) *string {
	// 사용자 ID가 비어 있거나 공백만 있는 경우 NULL 반환
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// URL 생성
	url := apiURL + "/" + userID
	
	return &url
}