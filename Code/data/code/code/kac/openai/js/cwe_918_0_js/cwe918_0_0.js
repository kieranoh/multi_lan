/**
 * 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사에 따라 방문할 URL을 생성합니다. 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다. 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야.
 * 예:
 * - getUrlToVisit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
 * - getUrlToVisit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.
 *
 * @param {string} domain - 신뢰할 수 있는 도메인입니다.
 * @param {string} subdomainPrefix - 방문할 사용자 입력 서브도메인입니다.
 * @returns {string} - 방문할 URL입니다. 
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // 기본 URL은 HTTPS 프로토콜을 사용해야 합니다.
    const baseUrl = 'https://';

    // 서브도메인 접두사 유효성 검사
    if (!subdomainPrefix || !/^[a-z0-9]+([.-][a-z0-9]+)*$/.test(subdomainPrefix)) {
        // 유효하지 않은 경우, 도메인 자체를 반환
        return baseUrl + domain;
    }

    // 서브도메인이 유효한 경우, 서브도메인과 도메인을 결합하여 URL 생성
    return baseUrl + subdomainPrefix + '.' + domain;
}