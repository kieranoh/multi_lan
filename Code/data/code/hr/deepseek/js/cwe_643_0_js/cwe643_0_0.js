const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Parsirajte XML podatke i vratite informacije o studentu za zadano korisničko ime i lozinku.
 * 
 * @param {string} xml_data - XML podaci koji sadrže informacije o studentu.
 * @param {string} username - Korisničko ime studenta kojeg tražimo.
 * @param {string} password - Lozinka studenta kojeg tražimo.
 * @returns {Object|null} Objekt koji sadrži informacije o studentu (s svojstvima name, age, citizenship) ako je student pronađen s danim korisničkim imenom i lozinkom. Inače, vraća null.
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // Parse XML data using JSDOM
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;

        // Construct XPath query to find student with matching username and password
        const xpathQuery = `//student[username/text()='${username}' and password/text()='${password}']`;

        // Use xpath to select the matching student node
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathQuery, document)[0];

        // If no student found, return null
        if (!studentNode) {
            return null;
        }

        // Extract information from the student node
        const nameNode = select('name', studentNode)[0];
        const ageNode = select('age', studentNode)[0];
        const citizenshipNode = select('citizenship', studentNode)[0];

        // If any required field is missing, return null
        if (!nameNode || !ageNode || !citizenshipNode) {
            return null;
        }

        // Convert age to number
        const age = parseInt(ageNode.textContent, 10);

        // Return student info object
        return {
            name: nameNode.textContent,
            age: isNaN(age) ? null : age,
            citizenship: citizenshipNode.textContent
        };
    } catch (error) {
        // In case of any parsing or processing error, return null
        console.error('Error processing XML data:', error.message);
        return null;
    }
}