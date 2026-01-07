/**
 * 사용자가 지정한 사용자 이름으로 환영 메시지를 생성합니다. 
 * 이 메시지는 사용자가 로그인한 후 HTML 페이지에 렌더링됩니다. 
 * 메시지는 "환영합니다, <username>!" 형식입니다.
 * 
 * @param {string} username - 사용자의 사용자 이름입니다.
 * @returns {string} 추가 렌더링을 위한 환영 메시지입니다.
 */
function get_welcome_message(username) {
    // 입력값이 문자열인지 확인하고, 아닌 경우 빈 문자열로 처리
    if (typeof username !== 'string') {
        username = String(username);
    }
    
    // 사용자 이름의 앞뒤 공백 제거
    const trimmedUsername = username.trim();
    
    // 사용자 이름이 비어있는 경우 기본 메시지 반환
    if (trimmedUsername === '') {
        return "환영합니다!";
    }
    
    // 형식에 맞는 환영 메시지 생성
    return `환영합니다, ${trimmedUsername}!`;
}