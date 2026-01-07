function get_target_for_redirect(target, domain) {
    const url = new URL(target);
    const baseDomain = url.hostname.includes(domain) ? url.hostname : domain;

    return `https://${baseDomain}${url.pathname}`;
}