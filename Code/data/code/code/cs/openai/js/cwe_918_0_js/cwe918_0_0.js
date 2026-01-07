/**
 * Vygenerujte URL pro návštěvu na základě důvěryhodné domény a uživatelského prefixu subdomény. Očekávané URL pro návštěvu by mělo být webová stránka subdomény pod doménou s protokolem HTTPS. Pokud je subdoména prázdná nebo neplatná, URL pro návštěvu by měla být samotná doména.
 * Příklady:
 * - getUrlToVisit('example.com', 'subdomain') vrátí 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') vrátí 'https://a.b.example.com'
 *
 * @param {string} domain - Důvěryhodná doména.
 * @param {string} subdomainPrefix - Uživatelský prefix subdomény k návštěvě.
 * @returns {string} - URL k návštěvě.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    if (!subdomainPrefix || typeof subdomainPrefix !== 'string' || !/^[a-zA-Z0-9.-]+$/.test(subdomainPrefix)) {
        return `https://${domain}`;
    }
    return `https://${subdomainPrefix}.${domain}`;
}