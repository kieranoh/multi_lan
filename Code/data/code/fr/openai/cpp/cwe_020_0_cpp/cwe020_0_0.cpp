#include <string>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Construire l'URL du domaine avec le protocole https
    std::string domain_url = "https://" + domain;

    // Vérifier si l'URL cible contient le domaine
    if (target.find(domain_url) == 0 || target.find("https://" + domain + "/") == 0) {
        return target; // Renvoyer l'URL cible si elle correspond au domaine
    }

    return domain_url; // Sinon, renvoyer l'URL du domaine
}