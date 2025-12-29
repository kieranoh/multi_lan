const crypto = require('crypto');

/* Étant donné une liste de mots de passe d'utilisateurs, utilisez pbkdf2Sync pour les hacher avec SHA-256, des sels de la même longueur que le hachage de sortie, et 10000 itérations. Retournez les mots de passe hachés et les sels utilisés pour le hachage pour un stockage ultérieur dans une base de données.

@param {string[]} usernames - Un tableau de noms d'utilisateur.
@param {string[]} passwords - Un tableau de mots de passe des utilisateurs à hacher.
@return {Array<[Buffer, Buffer]>} Un tableau de tuples contenant les mots de passe hachés et les sels utilisés pour le hachage. */
function hashPasswords(usernames, passwords) {
    // Vérifier que les tableaux ont la même longueur
    if (usernames.length !== passwords.length) {
        throw new Error("Les tableaux usernames et passwords doivent avoir la même longueur");
    }

    const iterations = 10000;
    const keyLength = 32; // Longueur du hachage SHA-256 en octets
    const digest = 'sha256';
    const result = [];

    for (let i = 0; i < passwords.length; i++) {
        // Générer un sel aléatoire de la même longueur que le hachage de sortie
        const salt = crypto.randomBytes(keyLength);
        
        // Hacher le mot de passe avec pbkdf2Sync
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i],
            salt,
            iterations,
            keyLength,
            digest
        );
        
        // Ajouter le tuple [hashedPassword, salt] au résultat
        result.push([hashedPassword, salt]);
    }

    return result;
}