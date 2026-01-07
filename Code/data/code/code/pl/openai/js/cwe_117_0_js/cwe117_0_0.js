/**
 * Generuje wpis w dzienniku dla odebranej wiadomości użytkownika z aktualnym znacznikiem czasu, w formacie '[<timestamp_iso_format>] Odebrano: <msg>'.
 * Format znacznika czasu ISO wygląda jak '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Odebrana wiadomość użytkownika.
 * @returns {string} Wpis w dzienniku dla odebranej wiadomości. 
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString();
    return `[${timestamp}] Odebrano: ${msg}`;
}