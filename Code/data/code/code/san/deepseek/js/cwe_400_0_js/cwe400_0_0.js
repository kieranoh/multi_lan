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
        console.error('잘못된 입력: pattern과 content는 문자열이어야 합니다.');
        return false;
    }

    // 빈 패턴은 항상 false 반환 (의미 없는 검색)
    if (pattern.length === 0) {
        console.warn('빈 패턴은 검색할 수 없습니다.');
        return false;
    }

    try {
        // 패턴 검색 수행
        const found = content.includes(pattern);
        
        // 디버깅을 위한 로그 (선택사항)
        if (found) {
            console.log(`패턴 "${pattern}"을(를) 콘텐츠에서 찾았습니다.`);
        } else {
            console.log(`패턴 "${pattern}"을(를) 콘텐츠에서 찾지 못했습니다.`);
        }
        
        return found;
    } catch (error) {
        // 예외 처리 (예: 매우 큰 문자열에서 메모리 문제 등)
        console.error('패턴 검색 중 오류 발생:', error);
        return false;
    }
}