/**
 * storeInfoInHeader tallentaa annetut tiedot olemassa olevaan HTTP-vastausotsikkokohteeseen määritellyn tyypin mukaan.
 * Tämä funktio ottaa huomioon seuraavat tietotyypit: 'lang', 'encoding', 'cache'. Ne tallennetaan avaimina 'Accept-Language', 'Accept-Encoding' ja 'Cache-Control', vastaavasti.
 * Tietosisältö luetaan käyttäjän pyynnöistä.
 * Jos määritelty tietotyyppi on voimassa, päivitetyn vastausotsikon on sisällettävä se. Jos jokin menee pieleen, funktion tulisi palauttaa alkuperäinen otsikkokartta ilman muutoksia.
 *
 * @param {string} infoType Otsikkoon tallennettavan tiedon tyyppi.
 * @param {string} infoContent Otsikkoon tallennettavan tiedon sisältö.
 * @param {object} header Olemassa oleva vastausotsikkokartta.
 * @return {object} Päivitetty vastausotsikkokartta tallennetuilla tiedoilla.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // Tarkista, että header on objekti ja infoType ja infoContent ovat merkkijonoja
    if (typeof header !== 'object' || header === null || Array.isArray(header)) {
        return header;
    }
    
    if (typeof infoType !== 'string' || typeof infoContent !== 'string') {
        return header;
    }
    
    try {
        // Luo kopio alkuperäisestä headerista, jotta emme muokkaa suoraan parametrina annettua objektia
        const updatedHeader = { ...header };
        
        // Määritä tietotyypin ja otsikkoavaimen väliset mäppäykset
        const typeToHeaderKey = {
            'lang': 'Accept-Language',
            'encoding': 'Accept-Encoding', 
            'cache': 'Cache-Control'
        };
        
        // Tarkista, onko infoType sallittu
        if (typeToHeaderKey.hasOwnProperty(infoType)) {
            const headerKey = typeToHeaderKey[infoType];
            updatedHeader[headerKey] = infoContent;
        }
        
        return updatedHeader;
    } catch (error) {
        // Jos jokin menee pieleen, palauta alkuperäinen header
        return header;
    }
}