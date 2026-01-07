/**
 * 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사에 따라 방문할 URL을 생성합니다.
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
    // 입력값 정규화
    const normalizedDomain = domain.trim();
    const normalizedSubdomain = subdomainPrefix.trim();
    
    // 서브도메인이 비어 있거나 유효하지 않은 경우 도메인 자체 반환
    if (!normalizedSubdomain || normalizedSubdomain.length === 0) {
        return `https://${normalizedDomain}`;
    }
    
    // 서브도메인 접두사 정리 (선행/후행 점 제거)
    const cleanedSubdomain = normalizedSubdomain.replace(/^\.+|\.+$/g, '');
    
    // 정리 후 서브도메인이 비어 있는 경우 도메인 자체 반환
    if (!cleanedSubdomain || cleanedSubdomain.length === 0) {
        return `https://${normalizedDomain}`;
    }
    
    // 유효한 서브도메인 형식 확인 (알파벳, 숫자, 점, 하이픈만 허용)
    const validSubdomainPattern = /^[a-zA-Z0-9][a-zA-Z0-9.-]*[a-zA-Z0-9]$/;
    if (!validSubdomainPattern.test(cleanedSubdomain)) {
        return `https://${normalizedDomain}`;
    }
    
    // 서브도메인 부분이 연속된 점을 포함하지 않는지 확인
    if (cleanedSubdomain.includes('..')) {
        return `https://${normalizedDomain}`;
    }
    
    // 각 레이블이 유효한지 확인 (각 부분이 1-63자이고 하이픈으로 시작하거나 끝나지 않음)
    const labels = cleanedSubdomain.split('.');
    const isValidLabel = labels.every(label => {
        return label.length >= 1 && 
               label.length <= 63 && 
               /^[a-zA-Z0-9][a-zA-Z0-9-]*[a-zA-Z0-9]$/.test(label);
    });
    
    if (!isValidLabel) {
        return `https://${normalizedDomain}`;
    }
    
    // 최종 URL 생성
    return `https://${cleanedSubdomain}.${normalizedDomain}`;
}