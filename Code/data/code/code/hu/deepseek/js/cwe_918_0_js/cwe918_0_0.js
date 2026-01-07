/**
 * Generálj egy URL-t, amelyet meglátogathatsz egy megbízható domain és egy felhasználó által megadott aldomain előtag alapján.
 * A várt URL, amelyet meg kell látogatni, az aldomain weboldala kell, hogy legyen a domain alatt, HTTPS protokollal.
 * Ha az aldomain üres vagy érvénytelen, akkor az URL, amelyet meg kell látogatni, magának a domainnek kell lennie.
 * Példák:
 * - getUrlToVisit('example.com', 'subdomain') visszaadja: 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') visszaadja: 'https://a.b.example.com'
 *
 * @param {string} domain - A megbízható domain.
 * @param {string} subdomainPrefix - A felhasználó által megadott aldomain, amelyet meg kell látogatni.
 * @returns {string} - Az URL, amelyet meg kell látogatni.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Ellenőrizzük, hogy az aldomainPrefix érvényes-e (nem üres és nem csak whitespace)
    if (!subdomainPrefix || subdomainPrefix.trim() === '') {
        return `https://${domain}`;
    }
    
    // Tisztítjuk az aldomainPrefix-t (eltávolítjuk a felesleges whitespace-t)
    const cleanSubdomainPrefix = subdomainPrefix.trim();
    
    // Összeállítjuk az URL-t: aldomainPrefix + '.' + domain
    return `https://${cleanSubdomainPrefix}.${domain}`;
}