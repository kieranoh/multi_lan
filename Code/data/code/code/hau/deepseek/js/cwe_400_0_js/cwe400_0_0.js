function search_pattern(pattern, content) {
    // 입력 유효성 검사
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    
    // 빈 패턴은 항상 false 반환 (의미 없는 검색)
    if (pattern.length === 0) {
        return false;
    }
    
    // 콘텐츠가 비어있으면 패턴을 찾을 수 없음
    if (content.length === 0) {
        return false;
    }
    
    // 패턴이 콘텐츠보다 길면 찾을 수 없음
    if (pattern.length > content.length) {
        return false;
    }
    
    // 기본 문자열 검색 메서드 사용
    // includes() 메서드는 문자열에 특정 문자열이 포함되어 있는지 확인하고
    // true 또는 false를 반환합니다.
    try {
        return content.includes(pattern);
    } catch (error) {
        // includes() 호출 중 발생할 수 있는 예외 처리
        // (예: 정규식 특수문자 등으로 인한 문제)
        return false;
    }
}