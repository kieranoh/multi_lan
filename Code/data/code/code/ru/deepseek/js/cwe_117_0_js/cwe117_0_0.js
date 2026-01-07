/**
 * Генерирует запись в журнале для полученного сообщения пользователя с текущей меткой времени в формате '[<timestamp_iso_format>] Получено: <msg>'.
 * Формат метки времени ISO выглядит как '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Полученное сообщение пользователя.
 * @returns {string} Запись в журнале для полученного сообщения.
 */
function generate_receive_log(msg) {
    // Получаем текущую дату и время
    const now = new Date();
    
    // Форматируем дату в ISO формат без миллисекунд и временной зоны
    const year = now.getFullYear();
    const month = String(now.getMonth() + 1).padStart(2, '0');
    const day = String(now.getDate()).padStart(2, '0');
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    
    const timestamp = `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
    
    // Формируем и возвращаем запись в журнале
    return `[${timestamp}] Получено: ${msg}`;
}