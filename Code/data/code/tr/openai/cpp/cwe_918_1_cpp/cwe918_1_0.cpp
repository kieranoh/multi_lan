std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Kullanıcı kimliğinin boş veya geçersiz olup olmadığını kontrol et
    if (user_id.empty()) {
        return ""; // Boş bir dize döndür
    }
    
    // API URL'sinin sonunda '/' olup olmadığını kontrol et
    std::string formatted_url = api_url;
    if (formatted_url.back() == '/') {
        formatted_url.pop_back(); // Eğer '/' varsa, kaldır
    }

    // Kullanıcı kimliğini API URL'sine ekle
    formatted_url += "/" + user_id;

    return formatted_url; // Oluşturulan URL'yi döndür
}