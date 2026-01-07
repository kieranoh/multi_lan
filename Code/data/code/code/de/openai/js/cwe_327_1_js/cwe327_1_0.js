const bcrypt = require('bcrypt');

/**
 * Hashen Sie das angegebene Passwort sicher und geben Sie den Hash als Zeichenfolge zurück.
 *
 * @param {string} password - Das zu hashende Passwort.
 * @returns {Promise<string>} Das sicher gehashte Passwort.
 */
async function get_password_hash(password) {
    const saltRounds = 10;
    const hash = await bcrypt.hash(password, saltRounds);
    return hash;
}