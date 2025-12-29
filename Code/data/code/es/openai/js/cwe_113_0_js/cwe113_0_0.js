function storeInfoInHeader(infoType, infoContent, header) {
    // Definimos un mapa que relaciona los tipos de información con las claves del encabezado
    const headerMap = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    };

    // Verificamos si el tipo de información es válido
    if (headerMap.hasOwnProperty(infoType)) {
        // Almacenamos el contenido en el encabezado correspondiente
        header[headerMap[infoType]] = infoContent;
    }

    // Devolvemos el encabezado, ya sea actualizado o sin cambios
    return header;
}