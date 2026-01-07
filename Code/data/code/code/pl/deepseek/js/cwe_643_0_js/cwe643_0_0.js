const { JSDOM } = require('jsdom');
const xpath = require('xpath');

function getStudentInfo(xml_data, username, password) {
    try {
        // Parse XML data using JSDOM
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const doc = dom.window.document;
        
        // Construct XPath query to find student with matching username and password
        const query = `//student[username/text()='${username}' and password/text()='${password}']`;
        
        // Use xpath to evaluate the query
        const select = xpath.useNamespaces({});
        const studentNode = select(query, doc)[0];
        
        // If no student found, return null
        if (!studentNode) {
            return null;
        }
        
        // Extract student information
        const nameNode = select('name', studentNode)[0];
        const ageNode = select('age', studentNode)[0];
        const citizenshipNode = select('citizenship', studentNode)[0];
        
        // Create and return student info object
        return {
            name: nameNode ? nameNode.textContent : '',
            age: ageNode ? parseInt(ageNode.textContent, 10) : 0,
            citizenship: citizenshipNode ? citizenshipNode.textContent : ''
        };
    } catch (error) {
        // In case of any parsing or processing errors, return null
        console.error('Error processing XML data:', error.message);
        return null;
    }
}