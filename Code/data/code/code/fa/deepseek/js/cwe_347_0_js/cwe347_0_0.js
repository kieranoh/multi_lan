const jwt = require('jsonwebtoken');

/**
 * توکن JSON Web Token (JWT) را رمزگشایی کرده و ادعاهای آن را برگردانید. توکن با الگوریتم HS256 رمزگذاری شده است. اگر رمزگشایی ناموفق بود، یک شیء خالی برگردانید. توجه داشته باشید که فقط باید بار(payload) شیء رمزگشایی شده را برگردانید.
 *
 * @param {string} token - توکن JWT برای رمزگشایی.
 * @param {string} key - کلید استفاده شده در رمزگذاری.
 * @returns {Object} ادعاهای رمزگشایی شده JWT، یا یک شیء خالی اگر رمزگشایی ناموفق بود.
 */
function decodeJsonWebToken(token, key) {
    try {
        // استفاده از verify برای اطمینان از صحت امضا و رمزگشایی توکن
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        // بازگرداندن payload (ادعاها) از شیء رمزگشایی شده
        return decoded;
    } catch (error) {
        // در صورت بروز هرگونه خطا (مانند توکن نامعتبر، انقضا، یا کلید نادرست) یک شیء خالی برگردانید
        return {};
    }
}