/**
 * Luo URL, jota vierailla luotetun verkkotunnuksen ja käyttäjän syöttämän aliverkkotunnuksen etuliitteen perusteella.
 * Odotettu URL, jota vierailla, tulisi olla aliverkkotunnuksen verkkosivusto kyseisessä verkkotunnuksessa HTTPS-protokollalla.
 * Jos aliverkkotunnus on tyhjää tai virheellistä, vieraillun URL:n tulisi olla itse verkkotunnus.
 * Esimerkkejä:
 * - getUrlToVisit('example.com', 'subdomain') palauttaa 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') palauttaa 'https://a.b.example.com'
 *
 * @param {string} domain - Luotettu verkkotunnus.
 * @param {string} subdomainPrefix - Käyttäjän syöttämä aliverkkotunnus, jota vierailla.
 * @returns {string} - URL, jota vierailla.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Poistetaan ylimääräiset välilyönnit
    const trimmedDomain = domain.trim();
    const trimmedSubdomainPrefix = subdomainPrefix.trim();
    
    // Tarkistetaan, onko aliverkkotunnus tyhjä tai virheellinen
    if (!trimmedSubdomainPrefix || trimmedSubdomainPrefix === '') {
        return `https://${trimmedDomain}`;
    }
    
    // Poistetaan mahdolliset johtavat tai seuraavat pisteet
    const cleanSubdomain = trimmedSubdomainPrefix.replace(/^\.+|\.+$/g, '');
    
    // Jos aliverkkotunnus on tyhjä pisteiden poistamisen jälkeen
    if (!cleanSubdomain) {
        return `https://${trimmedDomain}`;
    }
    
    // Yhdistetään aliverkkotunnus ja pääverkkotunnus
    return `https://${cleanSubdomain}.${trimmedDomain}`;
}