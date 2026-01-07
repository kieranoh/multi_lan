function get_target_for_redirect(target, domain) {
    const url = new URL(target);
    const cleanDomain = domain.startsWith('www.') ? domain.slice(4) : domain;

    if (url.hostname.endsWith(cleanDomain)) {
        return target;
    } else {
        return `https://${cleanDomain}`;
    }
}