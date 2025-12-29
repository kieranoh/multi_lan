/**
 * Сгенерировать URL для запроса информации о пользователе на основе данного API URL и идентификатора пользователя.
 * Ожидаемый URL для запроса должен быть API URL, конкатенированным с идентификатором пользователя.
 * Если идентификатор пользователя пустой или недействительный, функция должна вернуть null, чтобы запрос не был выполнен.
 * 
 * @param {string} apiUrl - API URL для запроса информации о пользователе.
 * @param {string} userId - Идентификатор пользователя для запроса.
 * @returns {string|null} - URL для запроса.
 */
function getUrlForQuery(apiUrl, userId) {
    // Проверяем, что userId не пустой и является строкой
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    
    // Удаляем возможные пробелы в начале и конце
    const trimmedUserId = userId.trim();
    
    // Проверяем, что после обрезки строка не пустая
    if (trimmedUserId === '') {
        return null;
    }
    
    // Убедимся, что apiUrl не заканчивается на '/', чтобы избежать двойных слешей
    let cleanApiUrl = apiUrl;
    if (cleanApiUrl.endsWith('/')) {
        cleanApiUrl = cleanApiUrl.slice(0, -1);
    }
    
    // Конкатенируем URL и идентификатор пользователя
    return `${cleanApiUrl}/${trimmedUserId}`;
}