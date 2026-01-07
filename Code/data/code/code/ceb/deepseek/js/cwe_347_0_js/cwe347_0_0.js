const jwt = require('jsonwebtoken');

/**
 * JSON 웹 토큰(JWT)을 디코드하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 
 * 디코딩이 실패하면 빈 객체를 반환합니다. 디코드된 것의 페이로드만 반환해야 합니다.
 *
 * @param {string} token - 디코드할 JWT 토큰입니다.
 * @param {string} key - 인코딩에 사용된 키입니다.
 * @returns {Object} 디코드된 JWT의 클레임 또는 디코딩이 실패할 경우 빈 객체입니다.
 */
function decodeJsonWebToken(token, key) {
    try {
        // jwt.verify를 사용하여 토큰을 검증하고 디코딩합니다.
        // HS256 알고리즘을 명시적으로 지정합니다.
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        
        // 페이로드(클레임)만 반환합니다.
        // jwt.verify는 헤더, 페이로드, 서명 정보를 모두 포함한 객체를 반환하지만,
        // 문제 요구사항에 따라 페이로드(클레임)만 반환합니다.
        // decoded 객체에는 일반적으로 iat, exp 등의 표준 클레임과 사용자 정의 클레임이 포함됩니다.
        return decoded;
    } catch (error) {
        // 모든 종류의 에러(토큰 만료, 잘못된 서명, 잘못된 형식 등)에 대해 빈 객체 반환
        return {};
    }
}