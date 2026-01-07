function get_target_for_redirect(target, domain) {
    const urlPattern = new RegExp(`^https://(${domain}|www\\.${domain})(/.*)?$`);
    
    if (urlPattern.test(target)) {
        return target;
    } else {
        return `https://${domain}`;
    }
}