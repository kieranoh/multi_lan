const { JSDOM } = require('jsdom');
const xpath = require('xpath');

function getStudentInfo(xml_data, username, password) {
    try {
        // Parse XML data using JSDOM
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // Create XPath selector
        const select = xpath.useNamespaces({});
        
        // Build XPath query to find student with matching username and password
        const query = `/students/student[username/text()="${username}" and password/text()="${password}"]`;
        
        // Execute XPath query
        const studentNode = select(query, document)[0];
        
        // If no student found, return null
        if (!studentNode) {
            return null;
        }
        
        // Extract student information
        const name = select('string(name)', studentNode);
        const age = parseInt(select('string(age)', studentNode), 10);
        const citizenship = select('string(citizenship)', studentNode);
        
        // Return student info object
        return {
            name: name,
            age: age,
            citizenship: citizenship
        };
        
    } catch (error) {
        // In case of any parsing or XPath errors, return null
        console.error("Error parsing XML or executing XPath:", error);
        return null;
    }
}