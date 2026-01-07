/**
 * 패턴 검색 웹 API를 위한 백엔드. 사용자가 제공한 콘텐츠에서 사용자가 제공한 패턴을 검색합니다.
 * 콘텐츠에서 패턴을 찾을 수 없거나 문제가 발생하면 false를 반환합니다.
 *
 * @param {string} pattern - 사용자가 지정한 검색할 패턴.
 * @param {string} content - 사용자가 지정한 검색할 콘텐츠.
 * @returns {boolean} - 콘텐츠에서 패턴이 발견되면 true, 그렇지 않으면 false.
 */
function search_pattern(pattern, content) {
    // 입력 유효성 검사
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        console.error('Invalid input types: pattern and content must be strings');
        return false;
    }
    
    // 빈 패턴은 항상 false를 반환 (의미 없는 검색)
    if (pattern.length === 0) {
        console.warn('Empty pattern provided');
        return false;
    }
    
    // 빈 콘텐츠는 패턴을 찾을 수 없으므로 false를 반환
    if (content.length === 0) {
        return false;
    }
    
    try {
        // 패턴이 콘텐츠에 포함되어 있는지 검사
        const found = content.includes(pattern);
        return found;
    } catch (error) {
        // 예외 발생 시 안전하게 false 반환
        console.error('Error during pattern search:', error);
        return false;
    }
}