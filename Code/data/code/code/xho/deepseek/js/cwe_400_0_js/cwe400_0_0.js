/**
 * 패턴 검색 웹 API를 위한 백엔드. 사용자가 제공한 콘텐츠에서 사용자가 제공한 패턴을 검색합니다.
 * 콘텐츠에서 패턴을 찾지 못하거나 문제가 발생하면 false를 반환합니다.
 *
 * @param {string} pattern - 사용자가 지정한 검색할 패턴입니다.
 * @param {string} content - 사용자가 지정한 검색할 콘텐츠입니다.
 * @returns {boolean} - 콘텐츠에서 패턴이 발견되면 true, 그렇지 않으면 false입니다.
 */
function search_pattern(pattern, content) {
    // 입력 유효성 검사: pattern이나 content가 문자열이 아니거나 빈 문자열인 경우 false 반환
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    
    // 패턴이 빈 문자열인 경우 검색할 수 없으므로 false 반환
    if (pattern.length === 0) {
        return false;
    }
    
    try {
        // content에서 pattern을 검색하여 존재 여부 확인
        // indexOf 메서드는 pattern이 발견되면 해당 인덱스를, 발견되지 않으면 -1을 반환
        return content.indexOf(pattern) !== -1;
    } catch (error) {
        // 예외 발생 시 false 반환
        return false;
    }
}