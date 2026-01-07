func getURLForQuery(apiURL, userID string) *string {
    // 사용자 ID가 비어 있거나 유효하지 않은 경우 NULL 반환
    if userID == "" {
        return nil
    }
    
    // URL 생성
    url := apiURL + "/" + userID
    
    return &url
}