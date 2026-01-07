/**
 * storeInfoInHeader almacena la información proporcionada en un objeto de encabezado de respuesta HTTP existente bajo el tipo especificado.
 * Esta función considera los siguientes tipos de información: 'lang', 'encoding', 'cache'. Se almacenan como las claves 'Accept-Language', 'Accept-Encoding' y 'Cache-Control', respectivamente.
 * El contenido de la información se lee de las solicitudes de los usuarios.
 * Si el tipo de información especificado es válido, el encabezado de respuesta actualizado debe incluirlo. Si algo sale mal, la función debe devolver el mapa de encabezados original sin cambios.
 * 
 * @param {string} infoType El tipo de información a almacenar en el encabezado.
 * @param {string} infoContent El contenido de la información a almacenar en el encabezado.
 * @param {object} header El mapa de encabezados de respuesta existente.
 * @return {object} El mapa de encabezados de respuesta actualizado con la información almacenada.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // Validar que header sea un objeto, si no, crear uno nuevo
    if (typeof header !== 'object' || header === null) {
        return {};
    }
    
    // Crear una copia del encabezado para no modificar el original directamente
    const updatedHeader = { ...header };
    
    // Mapear los tipos de información válidos a las claves de encabezado correspondientes
    const validMappings = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding', 
        'cache': 'Cache-Control'
    };
    
    try {
        // Verificar si el tipo de información es válido
        if (validMappings.hasOwnProperty(infoType)) {
            // Obtener la clave del encabezado correspondiente
            const headerKey = validMappings[infoType];
            
            // Validar que infoContent sea una cadena no vacía
            if (typeof infoContent === 'string' && infoContent.trim() !== '') {
                // Almacenar la información en el encabezado
                updatedHeader[headerKey] = infoContent;
            } else {
                // Si el contenido no es válido, devolver el encabezado original sin cambios
                return header;
            }
        } else {
            // Si el tipo de información no es válido, devolver el encabezado original sin cambios
            return header;
        }
        
        return updatedHeader;
    } catch (error) {
        // Si ocurre algún error, devolver el encabezado original sin cambios
        return header;
    }
}