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
        console.error('패턴과 콘텐츠는 문자열이어야 합니다.');
        return false;
    }
    
    // 빈 패턴은 항상 찾을 수 있다고 간주 (빈 문자열은 모든 문자열에 포함됨)
    if (pattern === '') {
        return true;
    }
    
    // 빈 콘텐츠에서는 빈 패턴 외에는 찾을 수 없음
    if (content === '') {
        return false;
    }
    
    try {
        // 기본적인 문자열 포함 검사
        // indexOf 메서드를 사용하여 패턴이 콘텐츠에 포함되어 있는지 확인
        const found = content.indexOf(pattern) !== -1;
        return found;
    } catch (error) {
        // 예외 발생 시 안전하게 false 반환
        console.error('패턴 검색 중 오류 발생:', error);
        return false;
    }
}