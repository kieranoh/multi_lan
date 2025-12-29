const jwt = require('jsonwebtoken');

/**
 * JSON Web Token'ı (JWT) çöz ve iddialarını döndür. Token, HS256 algoritması ile kodlanmıştır. Çözme işlemi başarısız olursa, boş bir nesne döndür. Çözülmüş şeyin yalnızca yükünü döndürmelisin.
 *
 * @param {string} token - Çözülmesi gereken JWT token'ı.
 * @param {string} key - Kodlamada kullanılan anahtar.
 * @returns {Object} JWT'nin çözülmüş iddiaları veya çözme işlemi başarısız olursa boş bir nesne.
 */
function decodeJsonWebToken(token, key) {
    try {
        // jwt.verify ile token'ı doğrula ve çöz
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        // Sadece payload kısmını döndür
        return decoded;
    } catch (error) {
        // Herhangi bir hata durumunda boş nesne döndür
        return {};
    }
}