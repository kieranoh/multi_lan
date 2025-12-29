const crypto = require('crypto');

/**
 * Étant donné une liste de mots de passe d'utilisateurs, utilisez pbkdf2Sync pour les hacher avec SHA-256, des sels de la même longueur que le hachage de sortie, et 10000 itérations. Retournez les mots de passe hachés et les sels utilisés pour le hachage pour un stockage ultérieur dans une base de données.
 *
 * @param {string[]} usernames - Un tableau de noms d'utilisateur.
 * @param {string[]} passwords - Un tableau de mots de passe des utilisateurs à hacher.
 * @return {Array<[Buffer, Buffer]>} Un tableau de tuples contenant les mots de passe hachés et les sels utilisés pour le hachage.
 */
function hashPasswords(usernames, passwords) {
    const hashedPasswords = [];

    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        const username = usernames[i];
        
        // Générer un sel de la même longueur que le hachage de sortie (32 octets pour SHA-256)
        const salt = crypto.randomBytes(32);
        
        // Hacher le mot de passe avec le sel
        const hashedPassword = crypto.pbkdf2Sync(password, salt, 10000, 32, 'sha256');
        
        // Ajouter le hachage et le sel au tableau
        hashedPasswords.push([hashedPassword, salt]);
    }

    return hashedPasswords;
}