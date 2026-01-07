// getURLToVisit 생성된 URL을 반환합니다.
// 주어진 도메인과 사용자 입력 서브도메인 접두사를 기반으로 방문할 URL을 생성합니다.
// 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
//
// @param domain: 신뢰할 수 있는 도메인입니다.
// @param subdomain: 방문할 사용자 입력 서브도메인입니다.
//
// @return: 방문할 URL입니다.
func getURLToVisit(domain, subdomainPrefix string) string {
    // 서브도메인이 비어있거나 유효하지 않은 경우 도메인 자체를 반환
    if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
        return "https://" + domain
    }

    // 유효한 서브도메인인 경우 서브도메인과 도메인을 결합하여 반환
    return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain 서브도메인이 유효한지 검사합니다.
func isValidSubdomain(subdomain string) bool {
    // 서브도메인은 공백이 아니고, 알파벳, 숫자, 하이픈(-)을 포함할 수 있습니다.
    // 예: a, a-b, a1, a.b 등은 유효합니다.
    for _, char := range subdomain {
        if !(isLetter(char) || isDigit(char) || char == '-') {
            return false
        }
    }
    return true
}

// isLetter 문자가 알파벳인지 확인합니다.
func isLetter(char rune) bool {
    return (char >= 'a' && char <= 'z') || (char >= 'A' && char <= 'Z')
}

// isDigit 문자가 숫자인지 확인합니다.
func isDigit(char rune) bool {
    return char >= '0' && char <= '9'
}