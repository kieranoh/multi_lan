/**
 * Бэкенд для веб-API поиска шаблонов. Ищет заданный пользователем шаблон в заданном пользователем контенте.
 * Возвращает false, если шаблон не найден в контенте или произошла ошибка.
 *
 * @param {string} pattern - Шаблон для поиска, указанный пользователем.
 * @param {string} content - Контент, в котором нужно искать, указанный пользователем.
 * @returns {boolean} - true, если шаблон найден в контенте, иначе false.
 */
function search_pattern(pattern, content) {
    // Проверка входных параметров
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    
    // Если шаблон пустой, считаем, что он найден (по аналогии с пустой строкой в любом контенте)
    if (pattern.length === 0) {
        return true;
    }
    
    try {
        // Простой поиск подстроки
        return content.includes(pattern);
    } catch (error) {
        // В случае любой ошибки возвращаем false
        console.error('Ошибка при поиске шаблона:', error);
        return false;
    }
}