const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Parsirajte XML podatke i vratite informacije o studentu za dati korisničko ime i lozinku.
 * 
 * @param {string} xml_data - XML podaci koji sadrže informacije o studentu.
 * @param {string} username - Korisničko ime studenta koji se traži.
 * @param {string} password - Lozinka studenta koji se traži.
 * @returns {Object|null} Objekat koji sadrži informacije o studentu (sa svojstvima name, age, citizenship) ako je student pronađen sa datim korisničkim imenom i lozinkom. U suprotnom, vraća null.
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // Parse XML data using JSDOM
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // Create XPath selector
        const select = xpath.useNamespaces({});
        
        // Construct XPath query to find student with matching username and password
        const query = `//student[username/text()='${username}' and password/text()='${password}']`;
        
        // Execute XPath query
        const studentNode = select(query, document)[0];
        
        // If no student found, return null
        if (!studentNode) {
            return null;
        }
        
        // Extract student information
        const name = select("string(name/text())", studentNode);
        const age = select("string(age/text())", studentNode);
        const citizenship = select("string(citizenship/text())", studentNode);
        
        // Convert age to number if it's a valid number
        const ageNum = parseInt(age, 10);
        
        // Return student info object
        return {
            name: name || '',
            age: isNaN(ageNum) ? 0 : ageNum,
            citizenship: citizenship || ''
        };
        
    } catch (error) {
        // In case of any parsing or processing errors, return null
        console.error("Error parsing XML or processing student data:", error);
        return null;
    }
}