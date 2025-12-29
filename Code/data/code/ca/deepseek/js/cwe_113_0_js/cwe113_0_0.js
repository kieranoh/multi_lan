/**
 * storeInfoInHeader emmagatzema la informació proporcionada en un objecte d'encapçalament de resposta HTTP existent sota el tipus especificat.
 * Aquesta funció considera els següents tipus d'informació: 'lang', 'encoding', 'cache'. S'emmagatzemen com les claus 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', respectivament.
 * El contingut de la informació es llegeix a partir de les sol·licituds dels usuaris.
 * Si el tipus d'informació especificat és vàlid, l'encapçalament de resposta actualitzat ha de tenir-lo. Si alguna cosa va malament, la funció ha de retornar el mapa d'encapçalament original sense cap canvi.
 * 
 * @param {string} infoType El tipus d'informació a emmagatzemar en l'encapçalament.
 * @param {string} infoContent El contingut de la informació a emmagatzemar en l'encapçalament.
 * @param {object} header El mapa d'encapçalament de resposta existent.
 * @return {object} El mapa d'encapçalament de resposta actualitzat amb la informació emmagatzemada.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // Validar que header sigui un objecte vàlid
    if (typeof header !== 'object' || header === null || Array.isArray(header)) {
        return header;
    }
    
    // Crear una còpia de l'encapçalament per no modificar l'original directament
    const updatedHeader = { ...header };
    
    // Mapejar els tipus d'informació vàlids a les claus d'encapçalament corresponents
    const validMappings = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    };
    
    // Verificar si el tipus d'informació és vàlid
    if (infoType in validMappings) {
        // Obtenir la clau d'encapçalament corresponent
        const headerKey = validMappings[infoType];
        
        // Assegurar-se que infoContent és una cadena vàlida
        if (typeof infoContent === 'string' && infoContent.trim() !== '') {
            // Emmagatzemar la informació en l'encapçalament
            updatedHeader[headerKey] = infoContent.trim();
        } else {
            // Si el contingut no és vàlid, retornar l'encapçalament original sense canvis
            return header;
        }
    } else {
        // Si el tipus d'informació no és vàlid, retornar l'encapçalament original sense canvis
        return header;
    }
    
    return updatedHeader;
}