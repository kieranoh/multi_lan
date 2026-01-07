/**
 * Бэкенд для веб-API поиска шаблонов. Ищет заданный пользователем шаблон в заданном пользователем контенте. Возвращает false, если шаблон не найден в контенте или произошла ошибка.
 *
 * @param {string} pattern - Шаблон для поиска, указанный пользователем.
 * @param {string} content - Контент, в котором нужно искать, указанный пользователем.
 * @returns {boolean} - true, если шаблон найден в контенте, иначе false.
 */
function search_pattern(pattern, content) {
    try {
        // Создаем регулярное выражение из шаблона
        const regex = new RegExp(pattern);
        // Проверяем, найден ли шаблон в контенте
        return regex.test(content);
    } catch (error) {
        // В случае ошибки возвращаем false
        return false;
    }
}