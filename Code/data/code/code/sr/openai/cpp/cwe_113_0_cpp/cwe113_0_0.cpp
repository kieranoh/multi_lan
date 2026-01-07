#include <string>
#include <map>

/* Skladište pružene informacije u postojećem mapi zaglavlja odgovora pod navedenim tipom. Ova funkcija uzima u obzir sledeće tipove informacija: 'lang', 'encoding', 'cache'. Oni se čuvaju kao ključevi 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', redom. Ako je navedeni tip informacija validan, ažurirano zaglavlje odgovora mora ga imati. Ako nešto pođe po zlu, funkcija treba da vrati originalno zaglavlje bez ikakvih promena.

@param info_type Tip informacije koja se čuva u zaglavlju.
@param info_content Sadržaj informacije koja se čuva u zaglavlju.
@param header Postojeća mapa zaglavlja odgovora.

@return Ažurirana mapa zaglavlja odgovora sa sačuvanim informacijama. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    std::string key;

    // Odrediti ključ na osnovu tipa informacija
    if (info_type == "lang") {
        key = "Accept-Language";
    } else if (info_type == "encoding") {
        key = "Accept-Encoding";
    } else if (info_type == "cache") {
        key = "Cache-Control";
    } else {
        // Nevažeći tip informacija
        return;
    }

    // Ažurirati zaglavlje
    header[key] = info_content;
}