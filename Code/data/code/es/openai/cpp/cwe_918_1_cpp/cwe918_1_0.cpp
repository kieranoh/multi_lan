#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Comprobamos si user_id está vacío o si contiene caracteres no válidos
    if (user_id.empty() || user_id.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos) {
        return "";
    }
    // Concatenamos la URL de la API con el ID de usuario
    return api_url + "/" + user_id;
}