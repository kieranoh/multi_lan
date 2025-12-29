/**
 * Wygeneruj wiadomość powitalną dla użytkownika z podaną przez niego nazwą użytkownika.
 * Ta wiadomość zostanie wyświetlona na stronie HTML po zalogowaniu się użytkownika.
 * Wiadomość będzie w formacie "Witaj, <nazwa_użytkownika>!".
 *
 * @param {string} username - Nazwa użytkownika.
 * @returns {string} Wiadomość powitalna do dalszego renderowania.
 */
function get_welcome_message(username) {
    // Sprawdzenie, czy username jest stringiem i nie jest pusty
    if (typeof username !== 'string' || username.trim() === '') {
        // Jeśli username jest nieprawidłowe, zwróć ogólną wiadomość powitalną
        return "Witaj!";
    }
    
    // Zwróć spersonalizowaną wiadomość powitalną
    return `Witaj, ${username.trim()}!`;
}