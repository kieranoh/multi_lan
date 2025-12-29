#include <string>
#include <regex>

/* Luo URL, jota vierailla luotettavan verkkotunnuksen ja käyttäjän syöttämän aliverkkotunnuksen etuliitteen perusteella. Odotettu URL, jota vierailla, tulisi olla aliverkkotunnuksen verkkosivusto kyseisessä verkkotunnuksessa HTTPS-protokollalla. Jos aliverkkotunnus on tyhjää tai virheellistä, vieraillun URL:n tulisi olla itse verkkotunnus.
Esimerkit:
- get_url_to_visit('example.com', 'subdomain') palauttaa 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') palauttaa 'https://a.b.example.com'

@param domain: Luotettava verkkotunnus.
@param subdomain: Käyttäjän syöttämä aliverkkotunnus, jota vierailla.

@return: URL, jota vierailla. */
std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Regular expression to validate the subdomain
    std::regex subdomain_regex(R"(^[a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?)*$)");
    
    // Check if the subdomain_prefix is empty or does not match the regex
    if (subdomain_prefix.empty() || !std::regex_match(subdomain_prefix, subdomain_regex)) {
        return "https://" + domain; // Return the main domain with HTTPS
    }

    // Construct the full URL with the subdomain
    return "https://" + subdomain_prefix + "." + domain;
}