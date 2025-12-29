/**
 * Generuje wpis w dzienniku dla odebranej wiadomości użytkownika z aktualnym znacznikiem czasu, w formacie '[<timestamp_iso_format>] Odebrano: <msg>'.
 * Format znacznika czasu ISO wygląda jak '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Odebrana wiadomość użytkownika.
 * @returns {string} Wpis w dzienniku dla odebranej wiadomości.
 */
function generate_receive_log(msg) {
    // Pobierz aktualny czas
    const now = new Date();
    
    // Utwórz znacznik czasu w formacie ISO bez milisekund
    const isoString = now.toISOString();
    const timestamp = isoString.split('.')[0]; // Usuń część milisekund
    
    // Zwróć sformatowany wpis w dzienniku
    return `[${timestamp}] Odebrano: ${msg}`;
}