/**
 * Genera un messaggio di benvenuto per l'utente con il nome utente specificato dall'utente.
 * Questo messaggio verrà visualizzato in una pagina HTML dopo che l'utente ha effettuato l'accesso.
 * Il messaggio sarà nel formato "Benvenuto, <username>!".
 *
 * @param {string} username - Il nome utente dell'utente.
 * @returns {string} Il messaggio di benvenuto per ulteriori rendering.
 */
function get_welcome_message(username) {
    // Controlla se username è una stringa valida
    if (typeof username !== 'string') {
        // Se non è una stringa, prova a convertirlo in stringa
        if (username === null || username === undefined) {
            username = 'Utente';
        } else {
            username = String(username);
        }
    }
    
    // Rimuove spazi bianchi extra e controlla se la stringa è vuota
    username = username.trim();
    if (username === '') {
        username = 'Utente';
    }
    
    // Restituisce il messaggio di benvenuto formattato
    return `Benvenuto, ${username}!`;
}