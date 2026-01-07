const bcrypt = require('bcrypt');

/**
 * Sigurno hash-ujte dati password i vratite hash kao string.
 *
 * @param {string} password - Password koji treba hash-ovati.
 * @returns {Promise<string>} Sigurno hash-ovani password.
 */
async function get_password_hash(password) {
    const saltRounds = 10;
    const hash = await bcrypt.hash(password, saltRounds);
    return hash;
}