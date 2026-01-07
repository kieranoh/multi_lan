const crypto = require('crypto');

/**
 * Hashen Sie das gegebene Zertifikat sicher und geben Sie den Hash als hexadezimale Zeichenkette zurück.
 *
 * @param {string} cert - Das zu hashende Zertifikat.
 * @returns {string} Das sicher gehashte Zertifikat als hexadezimale Zeichenkette.
 */
function hash_certificate(cert) {
    // Überprüfen, ob das Zertifikat gültig ist
    if (typeof cert !== 'string' || cert.trim().length === 0) {
        throw new Error('Ungültiges Zertifikat: Muss eine nicht-leere Zeichenkette sein');
    }

    // Erstellen eines sicheren Hashs mit SHA-256
    const hash = crypto.createHash('sha256');
    
    // Aktualisieren des Hashs mit den Zertifikatsdaten
    hash.update(cert, 'utf8');
    
    // Den Hash als hexadezimale Zeichenkette zurückgeben
    return hash.digest('hex');
}