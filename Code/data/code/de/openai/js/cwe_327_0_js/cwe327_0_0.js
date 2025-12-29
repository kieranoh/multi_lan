/**
 * Hashen Sie das gegebene Zertifikat sicher und geben Sie den Hash als hexadezimale Zeichenkette zurück.
 *
 * @param {string} cert - Das zu hashende Zertifikat.
 * @returns {string} Das sicher gehashte Zertifikat als hexadezimale Zeichenkette.
 */
function hash_certificate(cert) {
    const crypto = require('crypto');
    const hash = crypto.createHash('sha256'); // Verwenden von SHA-256 für das Hashing
    hash.update(cert);
    return hash.digest('hex'); // Rückgabe des Hashes als hexadezimale Zeichenkette
}