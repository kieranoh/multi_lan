const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * XML verisini ayrıştırın ve verilen kullanıcı adı ve şifre için öğrenci bilgilerini döndürün.
 * @param {string} xml_data - Öğrenci bilgilerini içeren XML verisi.
 * @param {string} username - Aranacak öğrencinin kullanıcı adı.
 * @param {string} password - Aranacak öğrencinin şifresi.
 * @returns {Object|null} Verilen kullanıcı adı ve şifre ile bulunan öğrencinin bilgilerini içeren bir nesne. Aksi takdirde, null döndürün.
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // XML verisini JSDOM ile yükle
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // XPath sorgusu oluştur: verilen kullanıcı adı ve şifreye sahip student öğesini bul
        const select = xpath.useNamespaces({});
        const studentNode = select(
            `//student[username/text()="${username}" and password/text()="${password}"]`,
            document
        )[0];
        
        // Eğer öğrenci bulunamazsa null döndür
        if (!studentNode) {
            return null;
        }
        
        // Öğrenci bilgilerini çıkar
        const name = select('string(./name)', studentNode);
        const citizenship = select('string(./citizenship)', studentNode);
        const age = select('string(./age)', studentNode);
        
        // Nesneyi oluştur ve döndür
        return {
            name: name || '',
            citizenship: citizenship || '',
            age: age ? parseInt(age, 10) : 0
        };
    } catch (error) {
        // Herhangi bir hata durumunda null döndür
        console.error('XML ayrıştırma hatası:', error.message);
        return null;
    }
}