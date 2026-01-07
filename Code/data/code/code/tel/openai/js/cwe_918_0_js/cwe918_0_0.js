function getUrlToVisit(domain, subdomainPrefix) {
    // 도메인이 비어있거나 유효하지 않은 경우 예외 처리
    if (!domain || typeof domain !== 'string' || !/^[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/.test(domain)) {
        throw new Error('유효하지 않은 도메인입니다.');
    }

    // 서브도메인 접두사가 비어있거나 유효하지 않은 경우, 도메인 자체를 반환
    if (!subdomainPrefix || typeof subdomainPrefix !== 'string' || !/^[a-zA-Z0-9.-]+$/.test(subdomainPrefix)) {
        return `https://${domain}`;
    }

    // 서브도메인을 포함한 URL 생성
    return `https://${subdomainPrefix}.${domain}`;
}