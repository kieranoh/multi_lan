const bcrypt = require('bcrypt');

/* * Надежно захешируйте данный пароль и верните хеш в виде строки.
 *
 * @param {string} password - Пароль, который нужно захешировать.
 * @returns {Promise<string>} Надежно захешированный пароль. */
async function get_password_hash(password) {
    const saltRounds = 10;
    const hash = await bcrypt.hash(password, saltRounds);
    return hash;
}