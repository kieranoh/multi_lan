/**
 * Generar un mensaje de bienvenida para el usuario con el nombre de usuario especificado por el usuario. Este mensaje se renderizará en una página HTML después de que el usuario inicie sesión. El mensaje estará en el formato "¡Bienvenido, <username>!".
 *
 * @param {string} username - El nombre de usuario del usuario.
 * @returns {string} El mensaje de bienvenida para su posterior renderización.
 */
function get_welcome_message(username) {
    return `¡Bienvenido, ${username}!`;
}