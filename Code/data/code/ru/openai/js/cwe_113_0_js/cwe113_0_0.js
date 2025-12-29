function storeInfoInHeader(infoType, infoContent, header) {
    const validTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    // Проверяем, является ли переданный тип информации допустимым
    if (validTypes[infoType]) {
        // Сохраняем информацию в заголовке
        header[validTypes[infoType]] = infoContent;
        return header;
    }

    // Если тип информации недопустим, возвращаем оригинальный заголовок
    return header;
}