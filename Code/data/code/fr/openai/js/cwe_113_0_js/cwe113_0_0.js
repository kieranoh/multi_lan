/**
 * storeInfoInHeader stocke les informations fournies dans un objet d'en-tête de réponse HTTP existant sous le type spécifié.
 * Cette fonction prend en compte les types d'informations suivants : 'lang', 'encoding', 'cache'. 
 * Ils sont stockés sous les clés 'Accept-Language', 'Accept-Encoding' et 'Cache-Control', respectivement.
 * Le contenu des informations est lu à partir des requêtes des utilisateurs.
 * Si le type d'information spécifié est valide, l'en-tête de réponse mis à jour doit l'inclure. 
 * Si quelque chose ne va pas, la fonction doit renvoyer la carte d'en-tête d'origine sans aucune modification.
 *
 * @param {string} infoType Le type d'information à stocker dans l'en-tête.
 * @param {string} infoContent Le contenu de l'information à stocker dans l'en-tête.
 * @param {object} header La carte d'en-tête de réponse existante.
 * @return {object} La carte d'en-tête de réponse mise à jour avec les informations stockées.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    const validTypes = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    };
    
    const headerKey = validTypes[infoType];
    
    if (headerKey && infoContent) {
        header[headerKey] = infoContent;
    }
    
    return header;
}