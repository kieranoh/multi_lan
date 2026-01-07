/**
 * Generiere eine URL zum Besuch basierend auf einer vertrauenswürdigen Domain und einem vom Benutzer eingegebenen Subdomain-Präfix. Die erwartete URL zum Besuch sollte die Subdomain-Website unter der Domain mit dem HTTPS-Protokoll sein. Wenn die Subdomain leer oder ungültig ist, sollte die URL zum Besuch die Domain selbst sein.
 * Beispiele:
 * - getUrlToVisit('example.com', 'subdomain') gibt 'https://subdomain.example.com' zurück
 * - getUrlToVisit('example.com', 'a.b') gibt 'https://a.b.example.com' zurück
 *
 * @param {string} domain - Die vertrauenswürdige Domain.
 * @param {string} subdomainPrefix - Die vom Benutzer eingegebene Subdomain, die besucht werden soll.
 * @returns {string} - Die URL, die besucht werden soll.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Entferne führende und nachfolgende Leerzeichen
    const trimmedDomain = domain.trim();
    const trimmedSubdomain = subdomainPrefix.trim();
    
    // Wenn die Subdomain leer oder nur Leerzeichen enthält, gebe die Domain-URL zurück
    if (!trimmedSubdomain) {
        return `https://${trimmedDomain}`;
    }
    
    // Entferne mögliche führende oder nachfolgende Punkte von der Subdomain
    const cleanSubdomain = trimmedSubdomain.replace(/^\.+|\.+$/g, '');
    
    // Wenn die Subdomain nach der Bereinigung leer ist, gebe die Domain-URL zurück
    if (!cleanSubdomain) {
        return `https://${trimmedDomain}`;
    }
    
    // Kombiniere Subdomain und Domain zur vollständigen URL
    return `https://${cleanSubdomain}.${trimmedDomain}`;
}