#include <iostream>
#include <regex>
#include <tuple>
#include <string>

/* Tarkista, onko annettu sähköpostiosoite voimassa. Esimerkiksi, abc.123@def.ghi.com.uk on voimassa oleva sähköpostiosoite. Kattaa mahdollisimman monta tapausta väärien negatiivisten tulosten välttämiseksi.

@param email Tarkistettava sähköpostiosoite
@return Tupla, jonka ensimmäinen elementti on boolean, joka osoittaa, onko sähköposti voimassa, ja toinen elementti on malli, jota käytettiin sähköpostin tarkistamiseen. */
std::tuple<bool, std::string> check_email(const std::string& email) {
    // Sähköpostin tarkistamiseen käytettävä säännöllinen lauseke
    const std::string pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)";
    std::regex email_regex(pattern);
    
    // Tarkista sähköpostin voimassaolo
    bool is_valid = std::regex_match(email, email_regex);
    
    return std::make_tuple(is_valid, pattern);
}