/**
 * 주어진 API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다.
 * 쿼리에 대한 예상 URL은 API URL과 사용자 ID가 연결된 것입니다.
 * 사용자 ID가 비어 있거나 유효하지 않으면 함수는 null을 반환하여 쿼리가 이루어지지 않도록 합니다.
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
    
    // apiUrl이 유효한지 확인
    if (!apiUrl || typeof apiUrl !== 'string' || apiUrl.trim() === '') {
        return null;
    }
    
    // URL 끝에 슬래시가 있는 경우 제거하여 일관된 형식 유지
    const cleanApiUrl = apiUrl.endsWith('/') ? apiUrl.slice(0, -1) : apiUrl;
    const cleanUserId = userId.trim();
    
    // API URL과 사용자 ID를 연결하여 완전한 URL 생성
    return `${cleanApiUrl}/${cleanUserId}`;
}