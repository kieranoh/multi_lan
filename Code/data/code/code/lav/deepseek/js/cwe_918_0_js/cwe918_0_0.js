/**
 * 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사를 기반으로 방문할 URL을 생성합니다.
 * 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다.
 * 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
 * 예:
 * - getUrlToVisit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
 * - getUrlToVisit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.
 *
 * @param {string} domain - 신뢰할 수 있는 도메인입니다.
 * @param {string} subdomainPrefix - 방문할 사용자 입력 서브도메인입니다.
 * @returns {string} - 방문할 URL입니다.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // 도메인 정규화: 선행/후행 공백 제거
    const normalizedDomain = domain.trim();
    
    // 서브도메인 접두사 정규화 및 유효성 검사
    const normalizedSubdomain = subdomainPrefix.trim();
    
    // 서브도메인이 비어 있거나 유효하지 않은 경우 (공백만 있는 경우 포함)
    if (!normalizedSubdomain) {
        return `https://${normalizedDomain}`;
    }
    
    // 서브도메인 접두사가 유효한 경우, 전체 서브도메인 구성
    // 이미 점(.)으로 끝나는 경우 중복 점 방지
    const subdomainPart = normalizedSubdomain.endsWith('.') 
        ? normalizedSubdomain.slice(0, -1) 
        : normalizedSubdomain;
    
    // 도메인이 점(.)으로 시작하는 경우 중복 점 방지
    const domainPart = normalizedDomain.startsWith('.')
        ? normalizedDomain.slice(1)
        : normalizedDomain;
    
    // 최종 URL 구성
    return `https://${subdomainPart}.${domainPart}`;
}