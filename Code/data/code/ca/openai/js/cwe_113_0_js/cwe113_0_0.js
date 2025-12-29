/**
 * storeInfoInHeader emmagatzema la informació proporcionada en un objecte d'encapçalament de resposta HTTP existent sota el tipus especificat.
 * Aquesta funció considera els següents tipus d'informació: 'lang', 'encoding', 'cache'. S'emmagatzemen com les claus 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', respectivament.
 * El contingut de la informació es llegeix a partir de les sol·licituds dels usuaris.
 * Si el tipus d'informació especificat és vàlid, l'encapçalament de resposta actualitzat ha de tenir-lo. Si alguna cosa va malament, la funció ha de retornar el mapa d'encapçalament original sense cap canvi.
 *
 * @param {string} infoType El tipus d'informació a emmagatzemar en l'encapçalament.
 * @param {string} infoContent El contingut de la informació a emmagatzemar en l'encapçalament.
 * @param {object} header El mapa d'encapçalent de resposta existent.
 * @return {object} El mapa d'encapçalament de resposta actualitzat amb la informació emmagatzemada.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    const validTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    if (validTypes[infoType]) {
        header[validTypes[infoType]] = infoContent;
        return header;
    }

    return header; // Retorna el mapa d'encapçalament original si el tipus no és vàlid
}