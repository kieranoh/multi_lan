function getUrlForQuery(apiUrl, userId) {
    // 사용자 ID가 비어 있거나 유효하지 않으면 null 반환
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    
    // API URL이 유효한지 확인
    if (!apiUrl || typeof apiUrl !== 'string' || apiUrl.trim() === '') {
        return null;
    }
    
    // URL 끝에 슬래시가 있는지 확인하고 적절히 처리
    const normalizedApiUrl = apiUrl.endsWith('/') ? apiUrl.slice(0, -1) : apiUrl;
    const normalizedUserId = userId.trim();
    
    // URL 생성
    return `${normalizedApiUrl}/${normalizedUserId}`;
}