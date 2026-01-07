function getUrlToVisit(domain, subdomainPrefix) {
    // 기본 URL을 HTTPS 프로토콜로 시작하도록 설정
    let url = 'https://';

    // 서브도메인 접두사가 비어 있거나 유효하지 않은 경우 도메인 자체를 사용할 것
    if (!subdomainPrefix || typeof subdomainPrefix !== 'string' || !/^[a-z0-9-]+(\.[a-z0-9-]+)*$/.test(subdomainPrefix)) {
        return url + domain; // 서브도메인이 유효하지 않으면 도메인만 반환
    }

    // 유효한 서브도메인인 경우 URL에 추가
    url += subdomainPrefix + '.' + domain;

    return url; // 최종 URL 반환
}