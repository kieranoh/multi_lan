/**
 * 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사에 따라 방문할 URL을 생성합니다.
 * 예상되는 방문 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다.
 * 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
 * 예:
 * - getUrlToVisit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
 * - getUrlToVisit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.
 *
 * @param {string} domain - 신뢰할 수 있는 도메인.
 * @param {string} subdomainPrefix - 방문할 사용자 입력 서브도메인.
 * @returns {string} - 방문할 URL.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // 입력값 정리: 양쪽 공백 제거
    const cleanDomain = domain.trim();
    const cleanSubdomain = subdomainPrefix.trim();
    
    // 서브도메인이 비어있거나 유효하지 않은 경우 도메인 자체 반환
    if (!cleanSubdomain || cleanSubdomain === '') {
        return `https://${cleanDomain}`;
    }
    
    // 서브도메인이 유효한 경우 조합하여 반환
    return `https://${cleanSubdomain}.${cleanDomain}`;
}