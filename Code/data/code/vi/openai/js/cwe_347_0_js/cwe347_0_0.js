const jwt = require('jsonwebtoken');

/**
 * Giải mã JSON Web Token (JWT) và trả về các tuyên bố của nó. Token được mã hóa bằng thuật toán HS256. Nếu việc giải mã thất bại, hãy trả về một đối tượng rỗng. Lưu ý rằng bạn chỉ nên trả về payload của đối tượng đã được giải mã.
 *
 * @param {string} token - Token JWT để giải mã.
 * @param {string} key - Khóa được sử dụng trong mã hóa.
 * @returns {Object} Các tuyên bố đã được giải mã của JWT, hoặc một đối tượng rỗng nếu việc giải mã thất bại. 
 */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        return {};
    }
}