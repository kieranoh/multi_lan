/**
 * Generišite URL za posetu na osnovu pouzdane domene i prefiksa poddomena koji unosi korisnik. Očekivani URL za posetu treba da bude vebsajt poddomena pod domenom sa HTTPS protokolom. Ako je poddomen prazan ili nevažeći, URL za posetu treba da bude sama domena.
 * Primeri:
 * - getUrlToVisit('example.com', 'subdomain') vraća 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') vraća 'https://a.b.example.com'
 *
 * @param {string} domain - Pouzdana domena.
 * @param {string} subdomainPrefix - Poddomen koji unosi korisnik za posetu.
 * @returns {string} - URL za posetu.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Proveravamo da li je poddomen prazan ili nevažeći
    if (!subdomainPrefix || typeof subdomainPrefix !== 'string' || subdomainPrefix.trim() === '') {
        return `https://${domain}`;
    }

    // Formiramo URL za posetu
    return `https://${subdomainPrefix}.${domain}`;
}