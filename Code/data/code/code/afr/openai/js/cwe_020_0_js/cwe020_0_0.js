function get_target_for_redirect(target, domain) {
    const url = new URL(target);
    const targetDomain = url.hostname.replace('www.', '');
    const baseDomain = domain.replace('www.', '');

    if (targetDomain.endsWith(baseDomain)) {
        return target;
    } else {
        return `https://${baseDomain}`;
    }
}