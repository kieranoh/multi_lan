function getUrlToVisit(domain, subdomainPrefix) {
    // 기본 URL은 HTTPS 프로토콜을 사용하는 도메인입니다.
    const baseUrl = `https://${domain}`;
    
    // 서브도메인이 비어 있거나 유효하지 않은 경우, 기본 URL을 반환합니다.
    if (!subdomainPrefix || !/^[a-z0-9]+([-.][a-z0-9]+)*$/i.test(subdomainPrefix)) {
        return baseUrl;
    }

    // 유효한 서브도메인을 포함한 URL을 반환합니다.
    return `https://${subdomainPrefix}.${domain}`;
}