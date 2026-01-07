function get_target_for_redirect(target, domain) {
    const url = new URL(target);
    const baseDomain = url.hostname.replace(/^www\./, '');

    if (baseDomain.endsWith(domain)) {
        return target;
    } else {
        return `https://${domain}`;
    }
}