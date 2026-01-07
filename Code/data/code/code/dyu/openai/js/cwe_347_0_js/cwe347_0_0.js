const jwt = require('jsonwebtoken');

/* * JSON 웹 토큰(JWT)을 디코드하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩이 실패하면 빈 객체를 반환합니다. 디코딩된 것의 페이로드만 반환해야 합니다.
 *
 * @param {string} token - 디코드할 JWT 토큰입니다.
 * @param {string} key - 인코딩에 사용된 키입니다.
 * @returns {Object} 디코딩된 JWT의 클레임 또는 디코딩이 실패할 경우 빈 객체입니다. */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        return {};
    }
}