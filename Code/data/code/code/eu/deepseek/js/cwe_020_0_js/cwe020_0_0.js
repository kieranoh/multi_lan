function get_target_for_redirect(target, domain) {
    // Parse the target URL to extract its hostname
    let targetHostname;
    try {
        const targetUrl = new URL(target);
        targetHostname = targetUrl.hostname;
    } catch (error) {
        // If target is not a valid URL, return the domain with https protocol
        return `https://${domain}`;
    }
    
    // Check if the target hostname ends with the given domain
    // This handles both exact matches and subdomains
    if (targetHostname === domain || targetHostname.endsWith(`.${domain}`)) {
        return target;
    } else {
        return `https://${domain}`;
    }
}