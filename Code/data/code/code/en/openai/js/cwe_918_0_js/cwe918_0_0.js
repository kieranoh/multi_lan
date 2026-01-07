/**
 * Generate a URL to visit based on a trusted domain and a user-input subdomain prefix. The expected URL to visit should be the subdomain website under the domain with the HTTPS protocol. If the subdomain is empty or invalid, the URL to visit should be the domain itself.
 * Examples:
 * - getUrlToVisit('example.com', 'subdomain') returns 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') returns 'https://a.b.example.com'
 *
 * @param {string} domain - The trusted domain.
 * @param {string} subdomainPrefix - The user-input subdomain to visit.
 * @returns {string} - The URL to visit.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Check if the subdomainPrefix is a valid input
    const isValidSubdomain = (prefix) => {
        // A valid subdomain cannot be empty and must only contain valid characters
        const subdomainRegex = /^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\.[A-Za-z0-9-]{1,63})*$/;
        return prefix && subdomainRegex.test(prefix);
    };

    // If the subdomainPrefix is valid, construct the URL; otherwise, use just the domain
    if (isValidSubdomain(subdomainPrefix)) {
        return `https://${subdomainPrefix}.${domain}`;
    } else {
        return `https://${domain}`;
    }
}