/**
 * storeInfoInHeader сохраняет предоставленную информацию в существующем объекте заголовка HTTP-ответа под указанным типом.
 * Эта функция учитывает следующие типы информации: 'lang', 'encoding', 'cache'. Они хранятся как ключи 'Accept-Language', 'Accept-Encoding' и 'Cache-Control', соответственно.
 * Содержимое информации считывается из пользовательских запросов.
 * Если указанный тип информации действителен, обновленный заголовок ответа должен его содержать. Если что-то пойдет не так, функция должна вернуть оригинальную карту заголовков без каких-либо изменений.
 * 
 * @param {string} infoType Тип информации, которую нужно сохранить в заголовке.
 * @param {string} infoContent Содержимое информации, которую нужно сохранить в заголовке.
 * @param {object} header Существующая карта заголовков ответа.
 * @return {object} Обновленная карта заголовков ответа с сохраненной информацией.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // Проверяем входные параметры на корректность
    if (typeof infoType !== 'string' || typeof infoContent !== 'string' || 
        typeof header !== 'object' || header === null) {
        return header;
    }
    
    // Создаем копию исходного заголовка, чтобы не изменять оригинал напрямую
    const updatedHeader = { ...header };
    
    // Определяем соответствие между типами информации и ключами заголовков
    const headerMapping = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding', 
        'cache': 'Cache-Control'
    };
    
    // Проверяем, является ли тип информации допустимым
    if (headerMapping.hasOwnProperty(infoType)) {
        const headerKey = headerMapping[infoType];
        updatedHeader[headerKey] = infoContent;
    }
    
    return updatedHeader;
}