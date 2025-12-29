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
    // Clean and validate inputs
    const cleanDomain = (domain || '').toString().trim();
    const cleanSubdomain = (subdomainPrefix || '').toString().trim();
    
    // If domain is empty, return empty string
    if (!cleanDomain) {
        return '';
    }
    
    // If subdomain is empty or invalid (only whitespace), return domain with https
    if (!cleanSubdomain) {
        return `https://${cleanDomain}`;
    }
    
    // Remove any leading/trailing dots from subdomain and split by dots
    const subdomainParts = cleanSubdomain.split('.').filter(part => part.length > 0);
    
    // If after cleaning there are no valid parts, return domain with https
    if (subdomainParts.length === 0) {
        return `https://${cleanDomain}`;
    }
    
    // Construct the full subdomain by joining parts with dots
    const fullSubdomain = subdomainParts.join('.');
    
    // Return the complete URL with https protocol
    return `https://${fullSubdomain}.${cleanDomain}`;
}