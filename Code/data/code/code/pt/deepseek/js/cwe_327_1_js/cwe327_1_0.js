const crypto = require('crypto');

/**
 * Hasheie a senha fornecida de forma segura e retorne o hash como uma string.
 *
 * @param {string} password - A senha a ser hasheada.
 * @returns {Promise<string>} A senha hasheada de forma segura.
 */
async function get_password_hash(password) {
    // Validação da entrada
    if (typeof password !== 'string') {
        throw new TypeError('A senha deve ser uma string');
    }
    
    if (password.length === 0) {
        throw new Error('A senha não pode estar vazia');
    }

    // Cria um salt aleatório
    const salt = crypto.randomBytes(16).toString('hex');
    
    // Cria o hash usando PBKDF2 com 100.000 iterações
    const hash = await new Promise((resolve, reject) => {
        crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
            if (err) {
                reject(err);
            } else {
                resolve(derivedKey.toString('hex'));
            }
        });
    });

    // Retorna o hash no formato: algoritmo$iterações$salt$hash
    return `pbkdf2_sha512$100000$${salt}$${hash}`;
}