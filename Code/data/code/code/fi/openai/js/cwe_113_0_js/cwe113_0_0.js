/**
 * storeInfoInHeader tallentaa annetut tiedot olemassa olevaan HTTP-vastausotsikkokohteeseen määritellyn tyypin mukaan.
 * Tämä funktio ottaa huomioon seuraavat tietotyypit: 'lang', 'encoding', 'cache'. Ne tallennetaan avaimina 'Accept-Language', 'Accept-Encoding' ja 'Cache-Control', vastaavasti.
 *Tietosisältö luetaan käyttäjän pyynnöistä.
 *Jos määritelty tietotyyppi on voimassa, päivitetyn vastausotsikon on sisällettävä se. Jos jokin menee pieleen, funktion tulisi palauttaa alkuperäinen otsikkokartta ilman muutoksia.
 *
 * @param {string} infoType Otsikkoon tallennettavan tiedon tyyppi.
 * @param {string} infoContent Otsikkoon tallennettavan tiedon sisältö.
 * @param {object} header Olemassa oleva vastausotsikkokartta.
 * @return {object} Päivitetty vastausotsikkokartta tallennetuilla tiedoilla.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    const validTypes = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    };

    if (validTypes[infoType]) {
        header[validTypes[infoType]] = infoContent;
        return header;
    }
    
    return header; // palautetaan alkuperäinen otsikkokartta virhetilanteessa
}