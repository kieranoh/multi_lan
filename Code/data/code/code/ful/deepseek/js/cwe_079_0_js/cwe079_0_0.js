/**
 * 사용자가 지정한 사용자 이름으로 환영 메시지를 생성합니다. 이 메시지는 사용자가 로그인한 후 HTML 페이지에 렌더링됩니다. 메시지는 "환영합니다, <username>!" 형식입니다.
 *
 * @param {string} username - 사용자의 사용자 이름입니다.
 * @returns {string} 추가 렌더링을 위한 환영 메시지입니다.
 */
function get_welcome_message(username) {
    if (typeof username !== 'string') {
        throw new TypeError('username must be a string');
    }
    
    const trimmedUsername = username.trim();
    
    if (trimmedUsername.length === 0) {
        throw new Error('username cannot be empty');
    }
    
    return `환영합니다, ${trimmedUsername}!`;
}