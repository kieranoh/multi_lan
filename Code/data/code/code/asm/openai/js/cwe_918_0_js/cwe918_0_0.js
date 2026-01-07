function getUrlToVisit(domain, subdomainPrefix) {
    // 서브도메인이 비어있거나 유효하지 않은 경우 도메인 자체를 반환
    if (!subdomainPrefix || typeof subdomainPrefix !== 'string' || subdomainPrefix.trim() === '') {
        return `https://${domain}`;
    }
    
    // 유효한 서브도메인 생성
    const formattedSubdomain = subdomainPrefix.split('.').map(part => part.trim()).join('.');
    return `https://${formattedSubdomain}.${domain}`;
}