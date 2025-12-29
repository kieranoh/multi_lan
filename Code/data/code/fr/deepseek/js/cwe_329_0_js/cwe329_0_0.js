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
    // Vérification des paramètres d'entrée
    if (!Buffer.isBuffer(key) || !Buffer.isBuffer(data)) {
        throw new TypeError('Les paramètres key et data doivent être des Buffer');
    }
    
    if (key.length < 16) {
        throw new Error('La clé doit contenir au moins 16 octets');
    }
    
    // Utiliser les 32 premiers octets (256 bits) pour AES-256-CBC
    // AES-256 nécessite 32 octets (256 bits), AES-192 nécessite 24 octets, AES-128 nécessite 16 octets
    // Nous utilisons AES-256 pour une sécurité maximale
    const keyLength = 32; // 256 bits pour AES-256
    const keyUsed = key.slice(0, keyLength);
    
    // Générer un IV aléatoire de 16 octets (taille standard pour AES)
    const iv = crypto.randomBytes(16);
    
    // Créer un chiffreur AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // Chiffrer les données
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: keyUsed
    };
}