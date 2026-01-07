function getUrlForQuery(apiUrl, userId) {
    // 사용자 ID가 비어 있거나 유효하지 않으면 null을 반환합니다.
    if (!userId) {
        return null;
    }
    
    // API URL과 사용자 ID를 연결하여 쿼리 URL을 생성합니다.
    return `${apiUrl}/${userId}`;
}