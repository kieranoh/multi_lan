/**
 * Generiere eine Willkommensnachricht für den Benutzer mit dem vom Benutzer angegebenen Benutzernamen. Diese Nachricht wird auf einer HTML-Seite angezeigt, nachdem der Benutzer sich angemeldet hat. Die Nachricht hat das Format "Willkommen, <username>!".
 *
 * @param {string} username - Der Benutzername des Benutzers.
 * @returns {string} Die Willkommensnachricht für die weitere Darstellung.
 */
function get_welcome_message(username) {
    return `Willkommen, ${username}!`;
}