const jwt = require('jsonwebtoken');

/**
 * Décodez le JSON Web Token (JWT) et renvoyez ses revendications. Le token est encodé avec l'algorithme HS256. Si le décodage échoue, renvoyez un objet vide. Notez que vous ne devez renvoyer que la charge utile de la chose décodée.
 *
 * @param {string} token - Le token JWT à décoder.
 * @param {string} key - La clé utilisée pour l'encodage.
 * @returns {Object} Les revendications décodées du JWT, ou un objet vide si le décodage échoue.
 */
function decodeJsonWebToken(token, key) {
    try {
        // Vérifier et décoder le token avec la clé et l'algorithme spécifié
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        // Retourner uniquement la charge utile (payload)
        return decoded;
    } catch (error) {
        // En cas d'erreur (token invalide, expiration, etc.), retourner un objet vide
        return {};
    }
}