/**
 * 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사를 기반으로 방문할 URL을 생성합니다.
 * 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다.
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
    // 도메인 정규화: 선행/후행 공백 제거
    const normalizedDomain = domain.trim();
    
    // 서브도메인 접두사 정규화 및 유효성 검사
    const normalizedSubdomain = subdomainPrefix.trim();
    
    // 서브도메인이 비어있거나 유효하지 않은 경우 (공백만 있거나 빈 문자열)
    if (!normalizedSubdomain || normalizedSubdomain === '') {
        return `https://${normalizedDomain}`;
    }
    
    // 서브도메인 접두사가 유효한 경우 전체 URL 구성
    // 서브도메인 부분의 점이 올바르게 처리되도록 함
    const cleanSubdomain = normalizedSubdomain.replace(/^\.+|\.+$/g, '');
    
    return `https://${cleanSubdomain}.${normalizedDomain}`;
}