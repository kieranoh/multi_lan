import (
	"strings"
)

func getURLForQuery(apiURL, userID string) *string {
	// 사용자 ID가 비어 있는지 확인
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	
	// API URL이 비어 있는지 확인
	if strings.TrimSpace(apiURL) == "" {
		return nil
	}
	
	// URL 생성
	url := strings.TrimSuffix(apiURL, "/") + "/" + userID
	
	return &url
}