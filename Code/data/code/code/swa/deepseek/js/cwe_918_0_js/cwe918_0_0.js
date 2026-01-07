/**
 * 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사를 기반으로 방문할 URL을 생성합니다.
 * 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다.
 * 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
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
    
    // 서브도메인이 비어 있거나 유효하지 않은 경우 (공백만 있거나 빈 문자열)
    if (!normalizedSubdomain || normalizedSubdomain.length === 0) {
        return `https://${normalizedDomain}`;
    }
    
    // 서브도메인 접두사가 유효한 경우 URL 생성
    // 서브도메인 접두사에 이미 점(.)이 포함되어 있을 수 있으므로 추가 점을 붙이지 않음
    const subdomainPart = normalizedSubdomain.endsWith('.') 
        ? normalizedSubdomain 
        : `${normalizedSubdomain}.`;
    
    return `https://${subdomainPart}${normalizedDomain}`;
}