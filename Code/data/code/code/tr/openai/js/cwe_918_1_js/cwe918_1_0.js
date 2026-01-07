/**
 * Verilen bir API URL'si ve bir kullanıcı kimliği temelinde kullanıcı bilgilerini sorgulamak için bir URL oluşturun. Sorgu için beklenen URL, API URL'sinin kullanıcı kimliği ile birleştirilmesiyle elde edilmelidir. Kullanıcı kimliği boş veya geçersizse, fonksiyon null döndürmelidir, böylece herhangi bir sorgu yapılmaz.
 * Örnekler:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') 'https://example.com/api/user/aBc123' döndürür
 * - getUrlForQuery('https://example.com/api/user', '') null döndürür
 *
 * @param {string} apiUrl - Kullanıcı bilgilerini sorgulamak için API URL'si.
 * @param {string} userId - Sorgulamak için kullanıcı kimliği.
 * @returns {string|null} - Sorgu için URL.
 */
function getUrlForQuery(apiUrl, userId) {
    if (!userId) {
        return null;
    }
    return `${apiUrl}/${userId}`;
}