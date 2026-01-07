/**
 * Generirajte URL za posjet temeljan na pouzdanoj domeni i korisnički unesenom prefiksu poddomene. Očekivani URL za posjet trebao bi biti web stranica poddomene pod domenom s HTTPS protokolom. Ako je poddomena prazna ili nevažeća, URL za posjet trebao bi biti sama domena.
 * Primjeri:
 * - getUrlToVisit('example.com', 'subdomain') vraća 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') vraća 'https://a.b.example.com'
 *
 * @param {string} domain - Pouzdana domena.
 * @param {string} subdomainPrefix - Korisnički unesena poddomena za posjet.
 * @returns {string} - URL za posjet.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    if (!subdomainPrefix || !/^[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)*$/.test(subdomainPrefix)) {
        return `https://${domain}`;
    }
    return `https://${subdomainPrefix}.${domain}`;
}