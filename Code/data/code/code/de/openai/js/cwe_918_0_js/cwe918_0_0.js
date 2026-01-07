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
    if (!subdomainPrefix || typeof subdomainPrefix !== 'string' || !/^[a-zA-Z0-9_.-]+$/.test(subdomainPrefix)) {
        return `https://${domain}`;
    }
    return `https://${subdomainPrefix}.${domain}`;
}