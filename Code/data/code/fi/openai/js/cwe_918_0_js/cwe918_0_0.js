/**
 * Luo URL, jota vierailla luotetun verkkotunnuksen ja käyttäjän syöttämän aliverkkotunnuksen etuliitteen perusteella. Odotettu URL, jota vierailla, tulisi olla aliverkkotunnuksen verkkosivusto kyseisessä verkkotunnuksessa HTTPS-protokollalla. Jos aliverkkotunnus on tyhjää tai virheellistä, vieraillun URL:n tulisi olla itse verkkotunnus.
 * Esimerkkejä:
 * - getUrlToVisit('example.com', 'subdomain') palauttaa 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') palauttaa 'https://a.b.example.com'
 *
 * @param {string} domain - Luotettu verkkotunnus.
 * @param {string} subdomainPrefix - Käyttäjän syöttämä aliverkkotunnus, jota vierailla.
 * @returns {string} - URL, jota vierailla.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Tarkistetaan, onko aliverkkotunnus tyhjää tai virheellistä
    if (!subdomainPrefix || typeof subdomainPrefix !== 'string' || subdomainPrefix.trim() === '') {
        return `https://${domain}`;
    }
    
    // Luodaan ja palautetaan URL aliverkkotunnuksella
    return `https://${subdomainPrefix}.${domain}`;
}