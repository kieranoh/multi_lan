/**
 * Vygenerujte URL pro dotazování informací o uživateli na základě dané API URL a ID uživatele. Očekávané URL pro dotaz by mělo být API URL spojené s ID uživatele. Pokud je ID uživatele prázdné nebo neplatné, funkce by měla vrátit null, aby nedošlo k provedení dotazu.
 * Příklady:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') vrací 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') vrací null
 *
 * @param {string} apiUrl - API URL pro dotazování informací o uživateli.
 * @param {string} userId - ID uživatele pro dotazování.
 * @returns {string|null} - URL pro dotaz.
 */
function getUrlForQuery(apiUrl, userId) {
    if (!userId) {
        return null;
    }
    return `${apiUrl}/${userId}`;
}