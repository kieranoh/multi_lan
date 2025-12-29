function get_target_for_redirect(target, domain) {
    const url = new URL(target);
    const targetDomain = url.hostname;

    if (targetDomain.endsWith(domain)) {
        return target;
    } else {
        return `https://${domain}`;
    }
}