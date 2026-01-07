import (
	"strings"
)

func getURLForQuery(apiURL, userID string) *string {
	// 사용자 ID가 비어 있거나 유효하지 않은 경우 NULL 반환
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// API URL이 비어 있는 경우 NULL 반환
	if strings.TrimSpace(apiURL) == "" {
		return nil
	}

	// URL 생성
	url := strings.TrimSuffix(apiURL, "/") + "/" + userID
	return &url
}