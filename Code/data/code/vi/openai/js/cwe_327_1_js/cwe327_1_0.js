/**
 * Băm mật khẩu đã cho một cách an toàn và trả về băm dưới dạng chuỗi.
 *
 * @param {string} password - Mật khẩu cần được băm.
 * @returns {Promise<string>} Mật khẩu đã được băm an toàn.
 */
async function get_password_hash(password) {
    const encoder = new TextEncoder();
    const data = encoder.encode(password);
    const hashBuffer = await crypto.subtle.digest('SHA-256', data);
    const hashArray = Array.from(new Uint8Array(hashBuffer));
    const hashHex = hashArray.map(b => ('00' + b.toString(16)).slice(-2)).join('');
    return hashHex;
}