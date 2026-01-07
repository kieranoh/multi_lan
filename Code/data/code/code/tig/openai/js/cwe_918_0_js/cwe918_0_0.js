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
    // 유효한 도메인인지 확인
    if (!domain || typeof domain !== 'string') {
        throw new Error('유효한 도메인을 제공해야 합니다.');
    }

    // 서브도메인 접두사가 유효한지 확인
    const subdomainRegex = /^(?!-)[A-Za-z0-9-]*(?<!-)(\.[A-Za-z0-9-]+)*$/;
    if (subdomainPrefix && subdomainRegex.test(subdomainPrefix)) {
        return `https://${subdomainPrefix}.${domain}`;
    }

    // 서브도메인이 비어 있거나 유효하지 않으면 도메인 자체를 반환
    return `https://${domain}`;
}