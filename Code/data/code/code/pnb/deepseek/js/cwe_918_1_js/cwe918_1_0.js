/**
 * 주어진 API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다.
 * 쿼리에 대한 예상 URL은 API URL과 사용자 ID가 연결된 것입니다.
 * 사용자 ID가 비어 있거나 유효하지 않으면 함수는 null을 반환하여 쿼리가 이루어지지 않도록 합니다.
 * 예시:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123')는 'https://example.com/api/user/aBc123'를 반환합니다.
 * - getUrlForQuery('https://example.com/api/user', '')는 null을 반환합니다.
 *
 * @param {string} apiUrl - 사용자 정보를 쿼리할 API URL입니다.
 * @param {string} userId - 쿼리할 사용자 ID입니다.
 * @returns {string|null} - 쿼리에 대한 URL입니다.
 */
function getUrlForQuery(apiUrl, userId) {
    // userId가 비어있거나 유효하지 않은 경우 null 반환
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    
    // API URL이 유효한지 확인
    if (!apiUrl || typeof apiUrl !== 'string' || apiUrl.trim() === '') {
        return null;
    }
    
    // API URL 끝에 슬래시가 있는지 확인하고 적절히 처리
    const normalizedApiUrl = apiUrl.endsWith('/') ? apiUrl.slice(0, -1) : apiUrl;
    const normalizedUserId = userId.trim();
    
    // URL 생성
    return `${normalizedApiUrl}/${normalizedUserId}`;
}