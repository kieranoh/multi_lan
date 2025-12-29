/**
 * Vytvoří uvítací zprávu pro uživatele s uživatelským jménem zadaným uživatelem.
 * Tato zpráva bude zobrazená na HTML stránce po přihlášení uživatele.
 * Zpráva bude ve formátu "Vítejte, <uživatelské_jméno>!".
 *
 * @param {string} username - Uživatelské jméno uživatele.
 * @returns {string} Uvítací zpráva pro další zobrazení.
 */
function get_welcome_message(username) {
    // Ošetření případu, kdy username není řetězec nebo je prázdný
    if (typeof username !== 'string') {
        username = String(username);
    }
    
    // Odstranění přebytečných bílých znaků
    const trimmedUsername = username.trim();
    
    // Kontrola, zda uživatelské jméno není prázdné po oříznutí
    if (trimmedUsername === '') {
        return "Vítejte!";
    }
    
    // Vrácení uvítací zprávy ve správném formátu
    return `Vítejte, ${trimmedUsername}!`;
}