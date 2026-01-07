import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	// 입력된 target URL을 파싱
	parsedURL, err := url.Parse(target)
	if err != nil {
		// 파싱 실패 시 도메인의 HTTPS URL 반환
		return "https://" + domain
	}

	// URL에 호스트가 없는 경우 도메인의 HTTPS URL 반환
	if parsedURL.Host == "" {
		return "https://" + domain
	}

	// 호스트가 도메인 또는 서브도메인인지 확인
	if strings.HasSuffix(parsedURL.Host, "."+domain) || parsedURL.Host == domain {
		// HTTPS 프로토콜 사용
		parsedURL.Scheme = "https"
		// URL 문자열로 변환하여 반환
		return parsedURL.String()
	}

	// 도메인에 속하지 않는 경우 도메인의 HTTPS URL 반환
	return "https://" + domain
}