const crypto = require('crypto');

/**
 * Надежно хешируйте данный сертификат и возвращайте хеш в виде шестнадцатичной строки.
 *
 * @param {string} cert - Сертификат, который нужно захешировать.
 * @returns {string} Надежно захешированный сертификат в виде шестнадцатичной строки.
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}