function getUrlToVisit(domain, subdomainPrefix) {
    // 기본적으로 HTTPS 프로토콜을 사용하여 도메인을 설정합니다.
    const protocol = 'https://';

    // 서브도메인이 비어있거나 유효하지 않은 경우 도메인만 반환합니다.
    if (!subdomainPrefix || !isValidSubdomain(subdomainPrefix)) {
        return protocol + domain;
    }

    // 서브도메인이 유효한 경우, 해당 서브도메인과 도메인을 조합하여 URL을 반환합니다.
    return protocol + subdomainPrefix + '.' + domain;
}

// 서브도메인 유효성을 검사하는 도우미 함수
function isValidSubdomain(subdomain) {
    // 서브도메인은 알파벳, 숫자, 하이픈으로 구성되며, 하이픈으로 시작하거나 끝날 수 없습니다.
    const subdomainRegex = /^(?!-)[A-Za-z0-9-]*(?<!-)$|^(?!-)[A-Za-z0-9-]+(\.[A-Za-z0-9-]+)*$/;
    return subdomainRegex.test(subdomain);
}