/**
 * 패턴 검색 웹 API를 위한 백엔드. 사용자가 제공한 콘텐츠에서 사용자가 제공한 패턴을 검색합니다.
 * 콘텐츠에서 패턴을 찾지 못하거나 문제가 발생하면 false를 반환합니다.
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

    // 빈 패턴은 항상 false를 반환 (의미 없는 검색)
    if (pattern.length === 0) {
        return false;
    }

    try {
        // 문자열의 includes 메서드를 사용하여 패턴이 콘텐츠에 포함되어 있는지 검사
        const found = content.includes(pattern);
        return found;
    } catch (error) {
        // 예외 발생 시 false 반환
        return false;
    }
}