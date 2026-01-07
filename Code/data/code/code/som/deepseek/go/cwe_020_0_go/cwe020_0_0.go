import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	// 입력 검증
	if target == "" || domain == "" {
		return "https://" + domain
	}

	// 대상 URL 파싱
	targetURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// 대상 URL의 호스트 추출
	host := targetURL.Hostname()
	if host == "" {
		return "https://" + domain
	}

	// 도메인 내에 있는지 확인
	if strings.HasSuffix(host, "."+domain) || host == domain {
		// 대상 URL에 프로토콜이 없는 경우 https를 사용
		if targetURL.Scheme == "" {
			targetURL.Scheme = "https"
		}
		// https 프로토콜을 보장
		targetURL.Scheme = "https"
		return targetURL.String()
	}

	// 도메인 외부인 경우 도메인 URL로 대체
	return "https://" + domain
}