#include <string>
#include <map>

/* Stockez les informations fournies dans une carte d'en-tête de réponse existante sous le type spécifié. 
Cette fonction prend en compte les types d'informations suivants : 'lang', 'encoding', 'cache'. 
Ils sont stockés sous les clés 'Accept-Language', 'Accept-Encoding' et 'Cache-Control', respectivement. 
Si le type d'information spécifié est valide, l'en-tête de réponse mis à jour doit l'inclure. 
Si quelque chose ne va pas, la fonction doit retourner l'en-tête original sans aucune modification.

@param info_type Le type d'information à stocker dans l'en-tête.
@param info_content Le contenu de l'information à stocker dans l'en-tête.
@param header La carte d'en-tête de réponse existante.

@return La carte d'en-tête de réponse mise à jour avec les informations stockées. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    }
    // Si le type d'information n'est pas valide, on ne fait rien et retourne l'en-tête original.
}