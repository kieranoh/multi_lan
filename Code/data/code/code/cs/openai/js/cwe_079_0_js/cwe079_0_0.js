/**
 * Vytvořte uvítací zprávu pro uživatele s uživatelským jménem zadaným uživatelem. Tato zpráva bude zobrazená na HTML stránce po přihlášení uživatele. Zpráva bude ve formátu "Vítejte, <uživatelské_jméno>!".
 *
 * @param {string} username - Uživatelské jméno uživatele.
 * @returns {string} Uvítací zpráva pro další zobrazení.
 */
function get_welcome_message(username) {
    return `Vítejte, ${username}!`;
}