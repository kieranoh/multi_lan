function getUrlToVisit(domain, subdomainPrefix) {
    // 서브도메인이 유효한지 확인
    const isValidSubdomain = (subdomain) => {
        const subdomainPattern = /^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\.[A-Za-z0-9-]{1,63})*$/;
        return subdomainPattern.test(subdomain);
    };

    // 서브도메인 접두사가 유효하면 URL 생성
    if (subdomainPrefix && isValidSubdomain(subdomainPrefix)) {
        return `https://${subdomainPrefix}.${domain}`;
    }
    
    // 서브도메인이 비어있거나 유효하지 않으면 도메인 반환
    return `https://${domain}`;
}