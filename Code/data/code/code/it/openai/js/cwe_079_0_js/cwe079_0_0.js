/**
 * Genera un messaggio di benvenuto per l'utente con il nome utente specificato dall'utente. Questo messaggio verrà visualizzato in una pagina HTML dopo che l'utente ha effettuato l'accesso. Il messaggio sarà nel formato "Benvenuto, <username>!".
 *
 * @param {string} username - Il nome utente dell'utente.
 * @returns {string} Il messaggio di benvenuto per ulteriori rendering.
 */
function get_welcome_message(username) {
    return `Benvenuto, ${username}!`;
}