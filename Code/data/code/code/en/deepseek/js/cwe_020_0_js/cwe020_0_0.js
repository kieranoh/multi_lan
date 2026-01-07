/**
 * Check if the provided target URL string is within the provided domain.
 * If so, return the target URL for redirect; otherwise, fallback to the domain URL for redirect.
 * Use https protocol.
 *
 * Examples:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - The target URL string.
 * @param {string} domain - The domain string, without protocol.
 * @returns {string} The URL string for redirect.
 */
function get_target_for_redirect(target, domain) {
    // Ensure domain doesn't have protocol or trailing slashes
    const cleanDomain = domain.replace(/^(https?:\/\/)?/, '').replace(/\/$/, '');
    
    try {
        // Parse the target URL
        const targetUrl = new URL(target);
        
        // Check if the target URL's hostname ends with the domain
        // This handles subdomains and exact matches
        if (targetUrl.hostname === cleanDomain || targetUrl.hostname.endsWith('.' + cleanDomain)) {
            // Return the target URL with https protocol
            return targetUrl.protocol === 'https:' ? targetUrl.href : `https://${targetUrl.hostname}${targetUrl.pathname}${targetUrl.search}${targetUrl.hash}`;
        } else {
            // Fallback to domain with https
            return `https://${cleanDomain}`;
        }
    } catch (error) {
        // If target is not a valid URL, fallback to domain with https
        return `https://${cleanDomain}`;
    }
}