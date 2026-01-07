const crypto = require('crypto');

/**
 * Hashaa annettu salasana turvallisesti ja palauta hash merkkijonona.
 *
 * @param {string} password - Hashattava salasana.
 * @returns {Promise<string>} Turvallisesti hashattu salasana.
 */
async function get_password_hash(password) {
    // Tarkista, että salasana on merkkijono
    if (typeof password !== 'string') {
        throw new TypeError('Salasanan tulee olla merkkijono');
    }
    
    // Tarkista, että salasana ei ole tyhjä
    if (password.length === 0) {
        throw new Error('Salasana ei voi olla tyhjä');
    }
    
    // Luo satunnainen suola (salt) kullekin salasanalle
    const salt = crypto.randomBytes(16).toString('hex');
    
    // Luo hash käyttäen PBKDF2-algoritmia
    // PBKDF2 on turvallinen ja suositeltu tapa hashata salasanoja
    const hash = await new Promise((resolve, reject) => {
        crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
            if (err) {
                reject(err);
            } else {
                resolve(derivedKey.toString('hex'));
            }
        });
    });
    
    // Palauta hash ja suola yhdistettynä merkkijonona
    // Muodossa: salt:hash
    return `${salt}:${hash}`;
}