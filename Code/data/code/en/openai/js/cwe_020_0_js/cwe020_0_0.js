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
    try {
        const url = new URL(target);
        const targetDomain = url.hostname;
        const baseDomain = domain.startsWith('www.') ? domain.slice(4) : domain;

        // Check if the target domain matches the provided domain or is a subdomain
        if (targetDomain.endsWith(baseDomain) || targetDomain === baseDomain) {
            return target; // Return the original target URL
        }
    } catch (error) {
        // If the URL parsing fails, we will fallback to the domain
        console.error("Invalid target URL, falling back to domain:", error);
    }
    // Fallback to the domain URL
    return `https://${domain}`;
}