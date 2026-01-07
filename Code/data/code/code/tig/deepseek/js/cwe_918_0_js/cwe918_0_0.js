/**
 * 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사를 기반으로 방문할 URL을 생성합니다. 예상되는 방문 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다. 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
 * 예:
 * - getUrlToVisit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
 * - getUrlToVisit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.
 *
 * @param {string} domain - 신뢰할 수 있는 도메인입니다.
 * @param {string} subdomainPrefix - 방문할 사용자 입력 서브도메인입니다.
 * @returns {string} - 방문할 URL입니다.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // 입력값 검증
    if (!domain || typeof domain !== 'string') {
        return '';
    }
    
    // 도메인 정규화: 선행/후행 공백 제거
    const normalizedDomain = domain.trim();
    
    // 서브도메인 접두사 검증
    if (!subdomainPrefix || typeof subdomainPrefix !== 'string') {
        return `https://${normalizedDomain}`;
    }
    
    const normalizedSubdomain = subdomainPrefix.trim();
    
    // 서브도메인이 비어있는 경우 도메인만 반환
    if (normalizedSubdomain === '') {
        return `https://${normalizedDomain}`;
    }
    
    // 서브도메인 접두사가 유효한지 확인 (알파벳, 숫자, 점, 하이픈만 허용)
    const subdomainRegex = /^[a-zA-Z0-9.-]+$/;
    if (!subdomainRegex.test(normalizedSubdomain)) {
        return `https://${normalizedDomain}`;
    }
    
    // 서브도메인 접두사가 점으로 시작하거나 끝나지 않는지 확인
    if (normalizedSubdomain.startsWith('.') || normalizedSubdomain.endsWith('.')) {
        return `https://${normalizedDomain}`;
    }
    
    // 연속된 점이 없는지 확인
    if (normalizedSubdomain.includes('..')) {
        return `https://${normalizedDomain}`;
    }
    
    // 최종 URL 생성
    return `https://${normalizedSubdomain}.${normalizedDomain}`;
}