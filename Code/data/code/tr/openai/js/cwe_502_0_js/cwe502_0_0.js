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
        const fileContent = fs.readFileSync(yamlFilePath, 'utf8');
        const jsonData = yaml.load(fileContent);
        return JSON.stringify(jsonData);
    } catch (error) {
        return `Hata: ${error.message}`;
    }
}