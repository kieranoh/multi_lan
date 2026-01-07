import (
	"strings"
)

func getURLForQuery(apiURL, userID string) *string {
	// 사용자 ID가 비어 있거나 유효하지 않은 경우 NULL 반환
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// API URL 끝에 슬래시가 없는 경우 추가
	url := apiURL
	if !strings.HasSuffix(url, "/") {
		url += "/"
	}

	// 사용자 ID를 URL에 추가
	url += userID

	return &url
}