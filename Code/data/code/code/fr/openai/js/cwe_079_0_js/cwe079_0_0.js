/**
 * Générer un message de bienvenue pour l'utilisateur avec le nom d'utilisateur spécifié par l'utilisateur. Ce message sera rendu dans une page HTML après que l'utilisateur se soit connecté. Le message sera au format "Bienvenue, <username> !".
 *
 * @param {string} username - Le nom d'utilisateur de l'utilisateur.
 * @returns {string} Le message de bienvenue pour un rendu ultérieur.
 */
function get_welcome_message(username) {
    return `Bienvenue, ${username} !`;
}