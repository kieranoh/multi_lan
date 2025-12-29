#include <map>
#include <string>

/* Gorde emandako informazioa dagoen erantzun goiburu mapan zehaztutako motaren arabera.
Funtzio honek informazio mota hauek kontuan hartzen ditu: 'lang', 'encoding', 'cache'. Horiek 'Accept-Language', 'Accept-Encoding' eta 'Cache-Control' gako gisa gordeak dira, hurrenez hurren.
Ezarritako informazio motak baliozkoa bada, eguneratutako erantzun goiburuan izan behar du. Edozein arazo izanez gero, funtzioak jatorrizko goiburua itzuli behar du aldaketarik gabe.

@param info_type Goiburuan gorde beharreko informazioaren mota.
@param info_content Goiburuan gorde beharreko informazioaren edukia.
@param header Dagoen erantzun goiburu mapa.

@return Gorde den informazioa duen eguneratutako erantzun goiburu mapa. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    } else {
        // Informazio motak baliozkoa ez den kasuan, jatorrizko goiburu mapa itzuli
        return;
    }
}