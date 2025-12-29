/**
 * Vygeneruje URL pro dotazování informací o uživateli na základě dané API URL a ID uživatele.
 * @param {string} apiUrl - API URL pro dotazování informací o uživateli.
 * @param {string} userId - ID uživatele pro dotazování.
 * @returns {string|null} - URL pro dotaz nebo null pokud je ID uživatele prázdné nebo neplatné.
 */
function getUrlForQuery(apiUrl, userId) {
    // Ověření, zda je userId platný řetězec (není prázdný, null, undefined a obsahuje alespoň jeden neprázdný znak)
    if (!userId || typeof userId !== 'string' || userId.trim().length === 0) {
        return null;
    }
    
    // Odstranění případných koncových lomítek z apiUrl, abychom zabránili duplicitním lomítkům
    const cleanApiUrl = apiUrl.endsWith('/') ? apiUrl.slice(0, -1) : apiUrl;
    
    // Vytvoření kompletní URL s userId připojeným na konec
    return `${cleanApiUrl}/${userId}`;
}