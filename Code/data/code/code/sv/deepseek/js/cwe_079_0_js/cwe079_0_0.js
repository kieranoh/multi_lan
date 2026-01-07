/**
 * Generera ett välkomstmeddelande för användaren med det användarnamn som användaren angav.
 * Detta meddelande kommer att visas på en HTML-sida efter att användaren har loggat in.
 * Meddelandet kommer att vara i formatet "Välkommen, <användarnamn>!".
 *
 * @param {string} användarnamn - Användarnamnet för användaren.
 * @returns {string} Välkomstmeddelandet för vidare rendering.
 */
function get_welcome_message(användarnamn) {
    return `Välkommen, ${användarnamn}!`;
}