/**
 * storeInfoInHeader emandako informazioa HTTP erantzun goiburu objektu batean gordetzen du zehaztutako motaren arabera.
 * Funtzio honek honako informazio motak kontuan hartzen ditu: 'lang', 'encoding', 'cache'.
 * Horiek 'Accept-Language', 'Accept-Encoding' eta 'Cache-Control' gako gisa gordetzen dira, hurrenez hurren.
 * Informazio edukiak erabiltzaile eskaeretatik irakurtzen dira.
 * Ezarritako informazio motak baliozkoa bada, eguneratutako erantzun goiburuan izan behar du.
 * Edozein arazo izanez gero, funtzioak jatorrizko goiburu mapa itzuli behar du aldaketarik gabe.
 *
 * @param {string} infoType - Gordetzeko motaren izena: 'lang', 'encoding' edo 'cache'.
 * @param {string} infoContent - Gordetzeko edukiaren balioa.
 * @param {Object} header - HTTP erantzun goiburuaren objektua.
 * @returns {Object} - Eguneratutako goiburu mapa, edo jatorrizkoa baliozko iritzirik ez badago.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    const validInfoTypes = ['lang', 'encoding', 'cache'];
    const headerKeys = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    if (validInfoTypes.includes(infoType) && infoContent) {
        header[headerKeys[infoType]] = infoContent;
    }

    return header;
}