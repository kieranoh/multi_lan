/**
 * Backend dla interfejsu API wyszukiwania wzorców. Wyszukuje podany przez użytkownika wzorzec w podanej przez użytkownika treści. Zwraca false, jeśli wzorzec nie zostanie znaleziony w treści lub jeśli wystąpi błąd.
 *
 * @param {string} pattern - Wzorzec do wyszukania, określony przez użytkownika.
 * @param {string} content - Treść, w której należy wyszukiwać, określona przez użytkownika.
 * @returns {boolean} - true, jeśli wzorzec został znaleziony w treści, false w przeciwnym razie.
 */
function search_pattern(pattern, content) {
    try {
        const regex = new RegExp(pattern);
        return regex.test(content);
    } catch (error) {
        return false;
    }
}