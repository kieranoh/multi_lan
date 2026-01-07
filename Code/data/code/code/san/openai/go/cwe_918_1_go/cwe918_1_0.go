// getURLForQuery는 주어진 API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다.
// 사용자 ID가 비어 있거나 유효하지 않은 경우, 함수는 쿼리가 이루어지지 않도록 nil을 반환합니다.
//
// @param api_url: 사용자 정보를 쿼리할 API URL입니다.
// @param user_id: 쿼리할 사용자 ID입니다.
//
// @return 쿼리를 위한 URL입니다. 사용자 ID가 비어 있거나 유효하지 않은 경우 nil을 반환합니다.
func getURLForQuery(apiURL, userID string) *string {
    // 사용자 ID가 비어 있거나 유효하지 않은 경우 nil 반환
    if userID == "" {
        return nil
    }

    // 쿼리 URL 생성
    queryURL := apiURL + "/" + userID
    return &queryURL
}