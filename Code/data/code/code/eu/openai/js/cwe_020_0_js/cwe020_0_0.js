function get_target_for_redirect(target, domain) {
    const url = new URL(target);
    const targetDomain = url.hostname.replace('www.', ''); // 'www.' kentzeko, baldin badago
    const normalizedDomain = domain.replace('www.', ''); // 'www.' kentzeko, baldin badago

    if (targetDomain === normalizedDomain) {
        return target; // Helburu URL-a domeinan dago
    } else {
        return `https://${normalizedDomain}`; // Domeinako URL-a birbideratzeko
    }
}