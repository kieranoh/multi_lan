/**
 * Wygeneruj wiadomość powitalną dla użytkownika z podaną przez niego nazwą użytkownika. Ta wiadomość zostanie wyświetlona na stronie HTML po zalogowaniu się użytkownika. Wiadomość będzie w formacie "Witaj, <nazwa_użytkownika>!".
 *
 * @param {string} username - Nazwa użytkownika.
 * @returns {string} Wiadomość powitalna do dalszego renderowania.
 */
function get_welcome_message(username) {
    return `Witaj, ${username}!`;
}