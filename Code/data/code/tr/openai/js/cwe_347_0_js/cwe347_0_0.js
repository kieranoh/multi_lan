const jwt = require('jsonwebtoken');

/* * JSON Web Token'ı (JWT) çöz ve iddialarını döndür. Token, HS256 algoritması ile kodlanmıştır. Çözme işlemi başarısız olursa, boş bir nesne döndür. Çözülmüş şeyin yalnızca yükünü döndürmelisin.
 *
 * @param {string} token - Çözülmesi gereken JWT token'ı.
 * @param {string} key - Kodlamada kullanılan anahtar.
 * @returns {Object} JWT'nin çözülmüş iddiaları veya çözme işlemi başarısız olursa boş bir nesne. */
function decodeJsonWebToken(token, key) {
    try {
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        return {};
    }
}