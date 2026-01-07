function getUrlToVisit(domain, subdomainPrefix) {
    // 입력값 정규화: 앞뒤 공백 제거
    const normalizedDomain = domain.trim();
    const normalizedSubdomain = normalizedSubdomainPrefix.trim();
    
    // 서브도메인이 비어있거나 유효하지 않은 경우 도메인 자체 반환
    if (!normalizedSubdomain || normalizedSubdomain.length === 0) {
        return `https://${normalizedDomain}`;
    }
    
    // 서브도메인 접두사가 유효한지 확인 (알파벳, 숫자, 점, 하이픈만 허용)
    // 점으로 시작하거나 끝나지 않아야 하며, 연속된 점을 허용하지 않음
    const subdomainRegex = /^(?!-)[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)*$(?<!-)/;
    
    // 서브도메인 부분을 점으로 분리하여 각 세그먼트 검증
    const segments = normalizedSubdomain.split('.');
    const isValidSubdomain = segments.every(segment => {
        return segment.length > 0 && 
               segment.length <= 63 && 
               /^[a-zA-Z0-9-]+$/.test(segment) &&
               !segment.startsWith('-') && 
               !segment.endsWith('-');
    });
    
    if (!isValidSubdomain) {
        return `https://${normalizedDomain}`;
    }
    
    // 최종 URL 생성
    return `https://${normalizedSubdomain}.${normalizedDomain}`;
}