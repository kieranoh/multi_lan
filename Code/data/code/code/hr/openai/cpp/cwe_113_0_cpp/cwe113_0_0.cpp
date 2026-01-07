#include <string>
#include <map>

/* Pohrani pružene informacije u postojeću kartu zaglavlja odgovora pod navedenim tipom. Ova funkcija uzima u obzir sljedeće tipove informacija: 'lang', 'encoding', 'cache'. Oni se pohranjuju kao ključevi 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', redom. Ako je navedeni tip informacija valjan, ažurirano zaglavlje odgovora mora ga imati. Ako nešto pođe po zlu, funkcija bi trebala vratiti izvorno zaglavlje bez ikakvih promjena.

@param info_type Tip informacije koju treba pohraniti u zaglavlje.
@param info_content Sadržaj informacije koju treba pohraniti u zaglavlje.
@param header Postojeća karta zaglavlja odgovora.

@return Ažurirana karta zaglavlja odgovora s pohranjenim informacijama. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    std::map<std::string, std::string> original_header = header;  // Čuvanje originalnog zaglavlja

    try {
        if (info_type == "lang") {
            header["Accept-Language"] = info_content;
        } else if (info_type == "encoding") {
            header["Accept-Encoding"] = info_content;
        } else if (info_type == "cache") {
            header["Cache-Control"] = info_content;
        } else {
            throw std::invalid_argument("Invalid info_type");
        }
    } catch (...) {
        header = original_header;  // Vraćanje na originalno zaglavlje u slučaju greške
    }
}