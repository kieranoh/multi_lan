/**
 * 사용자가 지정한 사용자 이름으로 환영 메시지를 생성합니다. 
 * 이 메시지는 사용자가 로그인한 후 HTML 페이지에 렌더링됩니다. 
 * 메시지는 "환영합니다, <username>!" 형식입니다.
 * 
 * @param {string} username - 사용자의 사용자 이름입니다.
 * @returns {string} 추가 렌더링을 위한 환영 메시지입니다.
 */
function get_welcome_message(username) {
    // 입력값 검증: username이 문자열인지 확인
    if (typeof username !== 'string') {
        throw new TypeError('username은 문자열이어야 합니다.');
    }
    
    // username이 빈 문자열이거나 공백만 있는 경우 기본값 처리
    const trimmedUsername = username.trim();
    if (trimmedUsername === '') {
        return '환영합니다, 손님!';
    }
    
    // XSS 방지를 위한 HTML 엔티티 이스케이프 처리
    const escapedUsername = trimmedUsername
        .replace(/&/g, '&amp;')
        .replace(/</g, '&lt;')
        .replace(/>/g, '&gt;')
        .replace(/"/g, '&quot;')
        .replace(/'/g, '&#x27;');
    
    // 환영 메시지 생성
    return `환영합니다, ${escapedUsername}!`;
}