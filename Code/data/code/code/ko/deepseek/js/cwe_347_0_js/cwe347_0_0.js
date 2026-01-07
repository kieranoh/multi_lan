const jwt = require('jsonwebtoken');

/**
 * JSON 웹 토큰(JWT)을 디코드하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 
 * 디코딩이 실패하면 빈 객체를 반환합니다. 디코드된 것의 페이로드만 반환해야 합니다.
 *
 * @param {string} token - 디코드할 JWT 토큰.
 * @param {string} key - 인코딩에 사용된 키.
 * @returns {Object} 디코드된 JWT의 클레임, 또는 디코딩이 실패하면 빈 객체.
 */
function decodeJsonWebToken(token, key) {
    try {
        // jwt.verify를 사용하여 토큰의 유효성을 검사하고 페이로드를 반환합니다.
        // HS256 알고리즘을 명시적으로 지정합니다.
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        // 페이로드만 반환합니다.
        return decoded;
    } catch (error) {
        // 디코딩이 실패하면 빈 객체를 반환합니다.
        return {};
    }
}