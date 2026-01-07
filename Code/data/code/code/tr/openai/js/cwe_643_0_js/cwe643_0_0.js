const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * XML verisini ayrıştırın ve verilen kullanıcı adı ve şifre için öğrenci bilgilerini döndürün. XML verisi aşağıdaki yapıya sahip olacaktır:
 * <students>
 *     <student>
 *         <username>john_doe</username>
 *         <password>jdpassword</password>
 *         <name>John Doe</name>
 *         <citizenship>USA</citizenship>
 *         <age>25</age>
 *     </student>
 *     <student>
 *         <username>bob_smith</username>
 *         <password>bspassword</password>
 *         <name>Bob Smith</name>
 *         <citizenship>Canada</citizenship>
 *         <age>22</age>
 *     </student>
 * </students>
 *
 * XML verisini JSDOM(xml_data, { contentType: "application/xml" }) ile yüklüyoruz.
 * Bir XPath sorgusu oluşturabiliriz ve bunu arama yapmak için kullanabiliriz.
 *
 * @param {string} xml_data - Öğrenci bilgilerini içeren XML verisi.
 * @param {string} username - Aranacak öğrencinin kullanıcı adı.
 * @param {string} password - Aranacak öğrencinin şifresi.
 * @returns {Object|null} Verilen kullanıcı adı ve şifre ile bulunan öğrencinin bilgilerini (isim, yaş, vatandaşlık özellikleri ile) içeren bir nesne. Aksi takdirde, null döndürün. 
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;
    const select = xpath.useNamespaces({"": "http://www.w3.org/1999/xhtml"});

    const query = `//student[username='${username}' and password='${password}']`;
    const studentNodes = select(query, doc);

    if (studentNodes.length > 0) {
        const student = studentNodes[0];
        return {
            name: student.getElementsByTagName('name')[0].textContent,
            age: student.getElementsByTagName('age')[0].textContent,
            citizenship: student.getElementsByTagName('citizenship')[0].textContent
        };
    }

    return null;
}