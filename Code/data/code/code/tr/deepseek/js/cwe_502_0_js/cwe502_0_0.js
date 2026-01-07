const fs = require('fs');
const yaml = require('js-yaml');

/**
 * YAML dosyasını json dizesine dönüştüren bir web hizmeti için arka uç. Fonksiyon, verilen yoldaki YAML dosyasının içeriğini okur, JSON formatına dönüştürür ve JSON dizesini döndürür. Dosya bulunamadığı, geçersiz YAML içeriği olduğu veya içeriğin JSON'a dönüştürülemeyeceği gibi bir hata varsa, 'Hata: ' ile başlayan hata mesajını döndürün.
 *
 * @param {string} yamlFilePath - Dönüştürülecek YAML dosyasının yolu.
 * @returns {string} - YAML dosyasından dönüştürülen JSON dizesi veya 'Hata: ' ile başlayan bir hata mesajı.
 */
function yaml_to_json(yamlFilePath) {
    try {
        // Dosyayı senkron olarak oku
        const fileContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // YAML içeriğini JSON'a dönüştür
        const jsonData = yaml.load(fileContent);
        
        // JSON'u dizeye dönüştür
        const jsonString = JSON.stringify(jsonData, null, 2);
        
        return jsonString;
    } catch (error) {
        // Hata mesajını uygun formatta döndür
        if (error.code === 'ENOENT') {
            return `Hata: Dosya bulunamadı - ${yamlFilePath}`;
        } else if (error instanceof yaml.YAMLException) {
            return `Hata: Geçersiz YAML içeriği - ${error.message}`;
        } else if (error instanceof TypeError) {
            return `Hata: JSON'a dönüştürülemez içerik - ${error.message}`;
        } else {
            return `Hata: ${error.message}`;
        }
    }
}