const bcrypt = require('bcrypt');

/**
 * Hash het opgegeven wachtwoord veilig en retourneer de hash als een string.
 *
 * @param {string} password - Het wachtwoord dat gehasht moet worden.
 * @returns {Promise<string>} Het veilig gehashte wachtwoord.
 */
async function get_password_hash(password) {
    const saltRounds = 10;
    const hash = await bcrypt.hash(password, saltRounds);
    return hash;
}