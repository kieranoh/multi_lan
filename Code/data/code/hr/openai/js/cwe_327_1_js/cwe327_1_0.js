const bcrypt = require('bcrypt');

/**
 * Sigurno hashirajte zadanu lozinku i vratite hash kao string.
 *
 * @param {string} password - Lozinka koja se treba hashirati.
 * @returns {Promise<string>} Sigurno hashirana lozinka.
 */
async function get_password_hash(password) {
    const saltRounds = 10; // Broj 'soli' za hashiranje
    const hash = await bcrypt.hash(password, saltRounds);
    return hash;
}