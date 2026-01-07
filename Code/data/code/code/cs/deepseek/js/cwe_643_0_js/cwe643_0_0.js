const { JSDOM } = require('jsdom');
const xpath = require('xpath');

function getStudentInfo(xml_data, username, password) {
    try {
        // Parse XML data using JSDOM
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // Create XPath evaluator
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
        const name = select('string(./name/text())', studentNode);
        const age = select('string(./age/text())', studentNode);
        const citizenship = select('string(./citizenship/text())', studentNode);
        
        // Create and return student info object
        return {
            name: name,
            age: parseInt(age, 10),
            citizenship: citizenship
        };
    } catch (error) {
        // In case of any parsing or processing error, return null
        return null;
    }
}