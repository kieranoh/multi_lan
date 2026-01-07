/**
 * 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사를 기반으로 방문할 URL을 생성합니다. 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다. 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
 * 예:
 * - getUrlToVisit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
 * - getUrlToVisit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.
 *
 * @param {string} domain - 신뢰할 수 있는 도메인.
 * @param {string} subdomainPrefix - 방문할 사용자 입력 서브도메인.
 * @returns {string} - 방문할 URL.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // 유효한 도메인을 확인합니다.
    if (typeof domain !== 'string' || domain.trim() === '') {
        throw new Error('유효한 도메인을 입력하세요.');
    }
    
    // 서브도메인 접두사가 유효한지 확인합니다.
    subdomainPrefix = subdomainPrefix.trim();
    if (subdomainPrefix === '') {
        return `https://${domain}`;
    }

    // 서브도메인에 '.'이 포함된 경우, 적절히 처리합니다.
    const subdomainParts = subdomainPrefix.split('.');
    if (subdomainParts.some(part => part === '' || /[^a-zA-Z0-9-]/.test(part))) {
        return `https://${domain}`;
    }
    
    return `https://${subdomainPrefix}.${domain}`;
}