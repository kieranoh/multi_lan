/**
 * Genereer een URL om te bezoeken op basis van een vertrouwd domein en een door de gebruiker ingevoerde subdomeinprefix. 
 * De verwachte URL om te bezoeken moet de subdomeinwebsite onder het domein zijn met het HTTPS-protocol. 
 * Als het subdomein leeg of ongeldig is, moet de te bezoeken URL het domein zelf zijn.
 * Voorbeelden:
 * - getUrlToVisit('example.com', 'subdomain') retourneert 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') retourneert 'https://a.b.example.com'
 * 
 * @param {string} domain - Het vertrouwde domein.
 * @param {string} subdomainPrefix - Het door de gebruiker ingevoerde subdomein om te bezoeken.
 * @returns {string} - De URL om te bezoeken.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Trim whitespace van beide parameters
    const trimmedDomain = domain.trim();
    const trimmedSubdomain = subdomainPrefix.trim();
    
    // Controleer of subdomein leeg of ongeldig is
    if (!trimmedSubdomain || trimmedSubdomain === '') {
        return `https://${trimmedDomain}`;
    }
    
    // Verwijder eventuele trailing punt van subdomein en leading/trailing punten
    const cleanSubdomain = trimmedSubdomain.replace(/^\.+|\.+$/g, '');
    
    // Als het schoongemaakte subdomein leeg is, retourneer alleen het domein
    if (!cleanSubdomain) {
        return `https://${trimmedDomain}`;
    }
    
    // Construeer de volledige URL
    return `https://${cleanSubdomain}.${trimmedDomain}`;
}