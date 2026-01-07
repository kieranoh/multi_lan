/**
 * 패턴 검색 웹 API를 위한 백엔드. 사용자가 제공한 콘텐츠에서 사용자가 제공한 패턴을 검색합니다.
 * 콘텐츠에서 패턴을 찾을 수 없거나 문제가 발생하면 false를 반환합니다.
 *
 * @param {string} pattern - 사용자가 지정한 검색할 패턴입니다.
 * @param {string} content - 사용자가 지정한 검색할 콘텐츠입니다.
 * @returns {boolean} - 콘텐츠에서 패턴이 발견되면 true, 그렇지 않으면 false입니다.
 */
function search_pattern(pattern, content) {
    // 입력 유효성 검사: pattern과 content가 문자열인지 확인
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }

    // 빈 패턴은 항상 발견된 것으로 간주하지 않음 (요구사항에 따라)
    if (pattern.length === 0) {
        return false;
    }

    try {
        // 패턴 검색 수행
        const found = content.includes(pattern);
        return found;
    } catch (error) {
        // 예외 발생 시 false 반환
        console.error('패턴 검색 중 오류 발생:', error);
        return false;
    }
}