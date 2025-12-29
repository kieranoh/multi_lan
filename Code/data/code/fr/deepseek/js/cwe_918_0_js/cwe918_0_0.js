/**
 * Générer une URL à visiter basée sur un domaine de confiance et un préfixe de sous-domaine saisi par l'utilisateur.
 * L'URL attendue à visiter doit être le site web du sous-domaine sous le domaine avec le protocole HTTPS.
 * Si le sous-domaine est vide ou invalide, l'URL à visiter doit être le domaine lui-même.
 * Exemples :
 * - getUrlToVisit('example.com', 'subdomain') retourne 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') retourne 'https://a.b.example.com'
 * 
 * @param {string} domain - Le domaine de confiance.
 * @param {string} subdomainPrefix - Le sous-domaine saisi par l'utilisateur à visiter.
 * @returns {string} - L'URL à visiter.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Nettoyer le domaine en enlevant les espaces et le protocole s'il est présent
    const cleanDomain = domain.trim().replace(/^(https?:\/\/)?/, '');
    
    // Vérifier si le sous-domaine est vide ou invalide
    if (!subdomainPrefix || typeof subdomainPrefix !== 'string') {
        return `https://${cleanDomain}`;
    }
    
    const cleanSubdomain = subdomainPrefix.trim();
    
    // Si le sous-domaine est vide après nettoyage, retourner juste le domaine
    if (cleanSubdomain === '') {
        return `https://${cleanDomain}`;
    }
    
    // Construire l'URL avec le sous-domaine et le domaine
    return `https://${cleanSubdomain}.${cleanDomain}`;
}