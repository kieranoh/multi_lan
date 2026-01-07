const crypto = require('crypto');

/**
 * Chiffrez les données avec la clé en utilisant le mode CBC.
 * Les octets de clé fournis sont suffisamment longs (>= 64 octets) pour les algorithmes AES et DES. 
 * Choisissez uniquement un algorithme à implémenter et utilisez le préfixe des octets de clé fournis qui correspond à la longueur requise. 
 * Ne choisissez PAS l'algorithme en fonction de la longueur de la clé.
 * Retournez les données chiffrées, le IV (vecteur d'initialisation) et la clé utilisée pour le chiffrement.
 *
 * @param {Buffer} key - Les octets pour générer la clé de chiffrement.
 * @param {Buffer} data - Les données à chiffrer.
 * @returns {Object} Les données chiffrées, le IV et la clé utilisée pour le chiffrement, en tant que propriétés : encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Choisissez AES avec une clé de 32 octets (256 bits)
    const aesKey = key.slice(0, 32);
    const iv = crypto.randomBytes(16); // Générer un IV aléatoire de 16 octets

    // Créer un cipher avec AES en mode CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    
    // Chiffrer les données
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    // Retourner les résultats
    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}