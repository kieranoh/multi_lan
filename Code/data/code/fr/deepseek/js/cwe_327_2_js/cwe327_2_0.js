const crypto = require('crypto');

/**
 * Chiffrez les données avec la clé en utilisant le mode CBC.
 * Les octets de clé fournis sont suffisamment longs (>= 64 octets) pour les algorithmes AES et DES. 
 * Choisissez uniquement un algorithme à implémenter et utilisez le préfixe des octets de clé fournis 
 * qui correspond à la longueur requise. Ne choisissez PAS l'algorithme en fonction de la longueur de la clé.
 * Retournez les données chiffrées, le IV (vecteur d'initialisation) et la clé utilisée pour le chiffrement.
 * 
 * @param {Buffer} key - Les octets pour générer la clé de chiffrement.
 * @param {Buffer} data - Les données à chiffrer.
 * @returns {Object} Les données chiffrées, le IV et la clé utilisée pour le chiffrement, 
 *                   en tant que propriétés : encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Vérification des paramètres d'entrée
    if (!Buffer.isBuffer(key) || !Buffer.isBuffer(data)) {
        throw new TypeError('Les paramètres key et data doivent être des Buffer');
    }
    
    if (key.length < 64) {
        throw new Error('La clé doit avoir au moins 64 octets');
    }
    
    // Choix de l'algorithme : AES-256-CBC (choix arbitraire comme spécifié)
    // Utilisation des 32 premiers octets de la clé pour AES-256
    const aesKeyLength = 32; // 256 bits
    const aesKey = key.slice(0, aesKeyLength);
    
    // Génération d'un IV aléatoire de 16 octets (taille standard pour AES)
    const iv = crypto.randomBytes(16);
    
    try {
        // Création du chiffreur AES-256-CBC
        const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
        
        // Chiffrement des données
        let encrypted = cipher.update(data);
        encrypted = Buffer.concat([encrypted, cipher.final()]);
        
        // Retourner le résultat sous forme d'objet
        return {
            encryptedData: encrypted,
            iv: iv,
            aesKey: aesKey
        };
    } catch (error) {
        // Gestion des erreurs de chiffrement
        throw new Error(`Erreur lors du chiffrement: ${error.message}`);
    }
}