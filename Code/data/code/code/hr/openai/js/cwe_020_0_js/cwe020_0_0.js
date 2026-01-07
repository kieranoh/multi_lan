function get_target_for_redirect(target, domain) {
    const url = new URL(target);
    const targetDomain = url.hostname;

    // Provjerava je li ciljni URL unutar zadane domene
    if (targetDomain.endsWith(domain)) {
        return target; // Vraća ciljni URL ako je unutar domene
    } else {
        return `https://${domain}`; // Vraća URL domene za preusmjeravanje
    }
}