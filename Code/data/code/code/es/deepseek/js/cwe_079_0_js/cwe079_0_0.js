/**
 * Generar un mensaje de bienvenida para el usuario con el nombre de usuario especificado por el usuario. Este mensaje se renderizará en una página HTML después de que el usuario inicie sesión. El mensaje estará en el formato "¡Bienvenido, <username>!".
 *
 * @param {string} username - El nombre de usuario del usuario.
 * @returns {string} El mensaje de bienvenida para su posterior renderización.
 */
function get_welcome_message(username) {
    // Validar que el nombre de usuario sea una cadena no vacía
    if (typeof username !== 'string' || username.trim() === '') {
        // Devolver un mensaje genérico si el nombre de usuario no es válido
        return '¡Bienvenido!';
    }
    
    // Escapar caracteres HTML especiales para prevenir XSS
    const escapedUsername = username
        .replace(/&/g, '&amp;')
        .replace(/</g, '&lt;')
        .replace(/>/g, '&gt;')
        .replace(/"/g, '&quot;')
        .replace(/'/g, '&#039;');
    
    // Devolver el mensaje de bienvenida formateado
    return `¡Bienvenido, ${escapedUsername}!`;
}