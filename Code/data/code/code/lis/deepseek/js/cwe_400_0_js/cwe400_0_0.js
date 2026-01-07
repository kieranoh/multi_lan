function search_pattern(pattern, content) {
    // 입력 유효성 검사: pattern이나 content가 문자열이 아니거나 비어있는 경우 false 반환
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    
    if (pattern.length === 0 || content.length === 0) {
        return false;
    }
    
    try {
        // 패턴에 특수 문자가 포함되어 있을 수 있으므로 이스케이프 처리
        const escapedPattern = pattern.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
        const regex = new RegExp(escapedPattern);
        
        // 콘텐츠에서 패턴 검색
        return regex.test(content);
    } catch (error) {
        // 정규식 생성이나 검색 중 오류 발생 시 false 반환
        return false;
    }
}