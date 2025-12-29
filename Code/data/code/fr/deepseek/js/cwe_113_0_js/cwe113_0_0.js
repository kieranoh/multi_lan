/**
 * storeInfoInHeader stocke les informations fournies dans un objet d'en-tête de réponse HTTP existant sous le type spécifié.
 * Cette fonction prend en compte les types d'informations suivants : 'lang', 'encoding', 'cache'. Ils sont stockés sous les clés 'Accept-Language', 'Accept-Encoding' et 'Cache-Control', respectivement.
 * Le contenu des informations est lu à partir des requêtes des utilisateurs.
 * Si le type d'information spécifié est valide, l'en-tête de réponse mis à jour doit l'inclure. Si quelque chose ne va pas, la fonction doit renvoyer la carte d'en-tête d'origine sans aucune modification.
 *
 * @param {string} infoType Le type d'information à stocker dans l'en-tête.
 * @param {string} infoContent Le contenu de l'information à stocker dans l'en-tête.
 * @param {object} header La carte d'en-tête de réponse existante.
 * @return {object} La carte d'en-tête de réponse mise à jour avec les informations stockées.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // Vérifier que header est un objet valide
    if (typeof header !== 'object' || header === null || Array.isArray(header)) {
        // Retourner l'en-tête d'origine si invalide
        return header;
    }
    
    // Créer une copie de l'en-tête pour éviter de modifier l'original
    const updatedHeader = { ...header };
    
    // Définir les correspondances entre les types d'info et les clés d'en-tête
    const typeToHeaderMap = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    };
    
    // Vérifier si le type d'information est valide
    if (typeToHeaderMap.hasOwnProperty(infoType)) {
        const headerKey = typeToHeaderMap[infoType];
        
        // Vérifier que le contenu est une chaîne non vide
        if (typeof infoContent === 'string' && infoContent.trim() !== '') {
            // Stocker l'information dans l'en-tête
            updatedHeader[headerKey] = infoContent;
            return updatedHeader;
        }
    }
    
    // Si quelque chose ne va pas, retourner l'en-tête d'origine
    return header;
}