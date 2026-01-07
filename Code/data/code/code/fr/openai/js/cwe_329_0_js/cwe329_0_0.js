const crypto = require('crypto');

/**
 * Chiffrez les données avec la clé en utilisant AES et le mode CBC.
 * Les octets de clé fournis sont suffisamment longs (>= 64 octets). Utilisez le préfixe des octets de clé fournis qui correspond à la longueur requise.
 * Retournez les données chiffrées, le vecteur d'initialisation (IV) et la clé utilisée pour le chiffrement.
 *
 * @param {Buffer} key - Les octets pour générer la clé de chiffrement (au moins 16 octets).
 * @param {Buffer} data - Les données à chiffrer.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} Les données chiffrées, l'IV et la clé utilisée pour le chiffrement.
 */
function encrypt_data(key, data) {
    const algorithm = 'aes-256-cbc';
    const iv = crypto.randomBytes(16); // Générer un vecteur d'initialisation aléatoire
    const keyUsed = key.slice(0, 32); // Utiliser les 32 premiers octets de la clé fournie

    const cipher = crypto.createCipheriv(algorithm, keyUsed, iv);
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: Buffer.from(encryptedData, 'hex'),
        iv: iv,
        keyUsed: keyUsed
    };
}