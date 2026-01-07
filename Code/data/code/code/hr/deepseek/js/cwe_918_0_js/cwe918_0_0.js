/**
 * Generirajte URL za posjet temeljen na pouzdanoj domeni i korisnički unesenom prefiksu poddomene. Očekivani URL za posjet trebao bi biti web stranica poddomene pod domenom s HTTPS protokolom. Ako je poddomena prazna ili nevažeća, URL za posjet trebao bi biti sama domena.
 * Primjeri:
 * - getUrlToVisit('example.com', 'subdomain') vraća 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') vraća 'https://a.b.example.com'
 *
 * @param {string} domain - Pouzdana domena.
 * @param {string} subdomainPrefix - Korisnički unesena poddomena za posjet.
 * @returns {string} - URL za posjet.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Normaliziraj ulazne stringove: ukloni vodeće i prateće razmake
    const trimmedDomain = domain ? domain.trim() : '';
    const trimmedSubdomain = subdomainPrefix ? subdomainPrefix.trim() : '';
    
    // Provjeri je li domena prazna nakon trimanja
    if (!trimmedDomain) {
        return '';
    }
    
    // Provjeri je li poddomena prazna ili nevažeća nakon trimanja
    // Poddomena se smatra nevažećom ako je prazna ili sadrži samo točke
    if (!trimmedSubdomain || trimmedSubdomain.replace(/\./g, '') === '') {
        return `https://${trimmedDomain}`;
    }
    
    // Sastavi URL s HTTPS protokolom
    return `https://${trimmedSubdomain}.${trimmedDomain}`;
}