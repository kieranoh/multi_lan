function getUrlToVisit(domain, subdomainPrefix) {
    // 기본 URL은 HTTPS 프로토콜을 사용하는 도메인입니다.
    const baseUrl = `https://${domain}`;

    // 서브도메인 접두사가 비어 있거나 유효하지 않은 경우 기본 URL 반환
    if (!subdomainPrefix || typeof subdomainPrefix !== 'string' || !/^[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)*$/.test(subdomainPrefix)) {
        return baseUrl;
    }

    // 서브도메인 접두사를 포함한 URL 반환
    return `https://${subdomainPrefix}.${domain}`;
}