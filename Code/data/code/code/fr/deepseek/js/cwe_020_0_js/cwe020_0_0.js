/**
 * Vérifie si l'URL cible fournie est dans le domaine fourni.
 * Si c'est le cas, renvoie l'URL cible pour la redirection ; sinon, revient à l'URL du domaine pour la redirection.
 * Utilise le protocole https.
 *
 * Exemples :
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - La chaîne d'URL cible.
 * @param {string} domain - La chaîne de domaine, sans protocole.
 * @returns {string} La chaîne d'URL pour la redirection.
 */
function get_target_for_redirect(target, domain) {
    // Vérification des paramètres d'entrée
    if (typeof target !== 'string' || typeof domain !== 'string') {
        return `https://${domain}`;
    }
    
    // Nettoyage des espaces blancs
    const trimmedTarget = target.trim();
    const trimmedDomain = domain.trim();
    
    // Si la cible est vide, retourner le domaine avec https
    if (!trimmedTarget) {
        return `https://${trimmedDomain}`;
    }
    
    try {
        // Créer un objet URL pour la cible
        let targetUrl;
        try {
            // Si la cible n'a pas de protocole, ajouter https:// temporairement pour l'analyse
            const targetToParse = trimmedTarget.includes('://') ? trimmedTarget : `https://${trimmedTarget}`;
            targetUrl = new URL(targetToParse);
        } catch (e) {
            // Si l'URL cible n'est pas valide, retourner le domaine avec https
            return `https://${trimmedDomain}`;
        }
        
        // Extraire le nom d'hôte de l'URL cible
        const targetHostname = targetUrl.hostname;
        
        // Vérifier si le domaine cible se termine par le domaine fourni
        // Cela permet de gérer les sous-domaines comme music.example.com
        if (targetHostname === trimmedDomain || targetHostname.endsWith(`.${trimmedDomain}`)) {
            // Retourner l'URL cible avec le protocole https
            return `https://${targetHostname}${targetUrl.pathname}${targetUrl.search}${targetUrl.hash}`;
        } else {
            // Retourner le domaine avec https
            return `https://${trimmedDomain}`;
        }
    } catch (error) {
        // En cas d'erreur inattendue, retourner le domaine avec https
        return `https://${trimmedDomain}`;
    }
}