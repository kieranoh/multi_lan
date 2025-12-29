#include <map>
#include <string>

/* Tallenna annettu tieto olemassa olevaan vastauspäätteen karttaan määritellyn tyypin mukaan. Tämä funktio ottaa huomioon seuraavat tietotyypit: 'lang', 'encoding', 'cache'. Ne tallennetaan avaimilla 'Accept-Language', 'Accept-Encoding' ja 'Cache-Control', vastaavasti. Jos määritelty tietotyyppi on voimassa, päivitetyn vastauspäätteen on sisällettävä se. Jos jokin menee pieleen, funktion tulisi palauttaa alkuperäinen päätteen ilman muutoksia.

@param info_type Tieto, joka tallennetaan päätteen.
@param info_content Tiedon sisältö, joka tallennetaan päätteen.
@param header Olemassa oleva vastauspäätteen kartta.

@return Päivitetty vastauspäätteen kartta tallennetulla tiedolla. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Määrittele avaimet eri tietotyypeille
    const std::string lang_key = "Accept-Language";
    const std::string encoding_key = "Accept-Encoding";
    const std::string cache_key = "Cache-Control";

    // Tarkista, mikä tietotyyppi on annettu ja tallenna vastaava avain ja arvo
    if (info_type == "lang") {
        header[lang_key] = info_content;
    } else if (info_type == "encoding") {
        header[encoding_key] = info_content;
    } else if (info_type == "cache") {
        header[cache_key] = info_content;
    } else {
        // Jos tietotyyppi ei ole voimassa, palautetaan alkuperäinen päätteen kartta ilman muutoksia
        return;
    }
}