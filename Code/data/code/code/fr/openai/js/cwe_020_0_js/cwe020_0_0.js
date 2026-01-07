function get_target_for_redirect(target, domain) {
    // Créez l'URL du domaine avec le protocole https
    const domainUrl = `https://${domain}`;
    
    // Vérifiez si l'URL cible commence par le domaine donné
    if (target.startsWith(domainUrl) || target.startsWith(`https://${domain}`)) {
        return target; // Retournez l'URL cible si elle est dans le domaine
    }
    
    return domainUrl; // Sinon, retournez l'URL du domaine pour la redirection
}