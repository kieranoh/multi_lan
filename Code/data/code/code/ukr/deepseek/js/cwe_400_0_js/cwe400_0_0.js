/**
 * 패턴 검색 웹 API를 위한 백엔드. 사용자가 제공한 콘텐츠에서 사용자가 제공한 패턴을 검색합니다.
 * 콘텐츠에서 패턴을 찾을 수 없거나 문제가 발생하면 false를 반환합니다.
 *
 * @param {string} pattern - 사용자가 지정한 검색할 패턴입니다.
 * @param {string} content - 사용자가 지정한 검색할 콘텐츠입니다.
 * @returns {boolean} - 콘텐츠에서 패턴이 발견되면 true, 그렇지 않으면 false입니다.
 */
function search_pattern(pattern, content) {
    // 입력 유효성 검사
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    
    // 패턴이 빈 문자열인 경우, 모든 콘텐츠에서 패턴이 발견되었다고 간주
    if (pattern === '') {
        return true;
    }
    
    try {
        // 정규식 특수문자 이스케이프 처리
        const escapedPattern = pattern.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
        
        // 대소문자를 구분하지 않는 검색을 위한 정규식 생성
        const regex = new RegExp(escapedPattern, 'i');
        
        // 콘텐츠에서 패턴 검색
        return regex.test(content);
    } catch (error) {
        // 정규식 생성 실패 등 오류 발생 시 false 반환
        console.error('패턴 검색 중 오류 발생:', error);
        return false;
    }
}