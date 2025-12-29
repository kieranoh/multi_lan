function get_target_for_redirect(target, domain) {
    const url = new URL(target);
    const domainWithProtocol = `https://${domain}`;
    
    if (url.hostname.endsWith(domain) || url.hostname === domain) {
        return target;
    } else {
        return domainWithProtocol;
    }
}