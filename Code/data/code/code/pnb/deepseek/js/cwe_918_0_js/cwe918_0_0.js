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
    // 입력값 검증: domain이 비어있거나 null/undefined인 경우 빈 문자열 반환
    if (!domain) {
        return '';
    }
    
    // domain에서 앞뒤 공백 제거
    domain = domain.trim();
    
    // subdomainPrefix가 비어있거나 유효하지 않은 경우 도메인 자체 반환
    if (!subdomainPrefix || subdomainPrefix.trim() === '') {
        return `https://${domain}`;
    }
    
    // subdomainPrefix에서 앞뒤 공백 제거
    subdomainPrefix = subdomainPrefix.trim();
    
    // subdomainPrefix가 유효한 서브도메인인지 확인
    // 서브도메인은 알파벳, 숫자, 하이픈, 점으로 구성될 수 있으며,
    // 하이픈으로 시작하거나 끝나지 않아야 하고, 연속된 점을 포함하지 않아야 합니다.
    const subdomainRegex = /^(?!-)[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)*(?<!-)$/;
    
    // 서브도메인 접두사가 유효하지 않은 경우 도메인 자체 반환
    if (!subdomainRegex.test(subdomainPrefix)) {
        return `https://${domain}`;
    }
    
    // 서브도메인 접두사와 도메인을 결합하여 URL 생성
    return `https://${subdomainPrefix}.${domain}`;
}