const bcrypt = require('bcrypt');

/* * Verilen şifreyi güvenli bir şekilde hash'le ve hash'i bir string olarak döndür.
 *
 * @param {string} password - Hash'lenecek şifre.
 * @returns {Promise<string>} Güvenli bir şekilde hash'lenmiş şifre. */
async function get_password_hash(password) {
    const saltRounds = 10;
    const hash = await bcrypt.hash(password, saltRounds);
    return hash;
}