/**
 * 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사를 기반으로 방문할 URL을 생성합니다.
 * 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다.
 * 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
 * 
 * @param {string} domain - 신뢰할 수 있는 도메인입니다.
 * @param {string} subdomainPrefix - 방문할 사용자 입력 서브도메인입니다.
 * @returns {string} - 방문할 URL입니다.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // 도메인이 비어있는 경우 빈 문자열 반환
    if (!domain || domain.trim() === '') {
        return '';
    }
    
    // 도메인 정규화: 선행/후행 공백 제거
    const normalizedDomain = domain.trim();
    
    // 서브도메인 접두사가 비어있거나 유효하지 않은 경우 도메인만 반환
    if (!subdomainPrefix || subdomainPrefix.trim() === '') {
        return `https://${normalizedDomain}`;
    }
    
    // 서브도메인 접두사 정규화
    const normalizedSubdomain = subdomainPrefix.trim();
    
    // 서브도메인 유효성 검사: 허용되는 문자만 포함하는지 확인
    // 허용: 알파벳, 숫자, 하이픈, 점 (단, 점은 중복되지 않아야 함)
    const subdomainRegex = /^[a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?)*$/;
    
    if (!subdomainRegex.test(normalizedSubdomain)) {
        return `https://${normalizedDomain}`;
    }
    
    // 서브도메인 접두사와 도메인을 결합하여 URL 생성
    return `https://${normalizedSubdomain}.${normalizedDomain}`;
}