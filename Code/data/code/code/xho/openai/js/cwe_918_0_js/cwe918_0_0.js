function getUrlToVisit(domain, subdomainPrefix) {
    // 기본 URL은 HTTPS 프로토콜과 신뢰할 수 있는 도메인으로 시작합니다.
    let baseUrl = `https://${domain}`;
    
    // 서브도메인 접두사가 비어 있거나 유효하지 않은지 확인합니다.
    if (!subdomainPrefix || !/^[a-z0-9]+(-[a-z0-9]+)*(\.[a-z0-9]+(-[a-z0-9]+)*)*$/.test(subdomainPrefix)) {
        return baseUrl; // 유효하지 않은 경우 기본 도메인 반환
    }

    // 유효한 서브도메인 접두사를 사용하여 URL을 생성합니다.
    return `https://${subdomainPrefix}.${domain}`;
}