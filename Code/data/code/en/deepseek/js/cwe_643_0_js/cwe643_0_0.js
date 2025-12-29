const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * Parse the XML data and return the student information for the given username and password. The XML data will have the following structure:
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
 * We load the XML data with JSDOM(xml_data, { contentType: "application/xml" })
 * We can construct a XPath query and use it to search.
 *
 * @param {string} xml_data - The XML data containing the student information.
 * @param {string} username - The username of the student to search for.
 * @param {string} password - The password of the student to search for.
 * @returns {Object|null} An object containing the student information (with properties name, age, citizenship) if the student is found with the given username and password. Otherwise, return null.
 */
function getStudentInfo(xml_data, username, password) {
    // Parse the XML data using JSDOM
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;
    
    // Create an XPath evaluator
    const select = xpath.useNamespaces({});
    
    // Construct XPath query to find student with matching username and password
    const query = `//student[username/text()="${username}" and password/text()="${password}"]`;
    
    try {
        // Execute the XPath query
        const studentNode = select(query, doc, true);
        
        // If no student found, return null
        if (!studentNode) {
            return null;
        }
        
        // Extract the required information from the student node
        const nameNode = select("name/text()", studentNode, true);
        const citizenshipNode = select("citizenship/text()", studentNode, true);
        const ageNode = select("age/text()", studentNode, true);
        
        // If any required field is missing, return null
        if (!nameNode || !citizenshipNode || !ageNode) {
            return null;
        }
        
        // Convert age to number
        const age = parseInt(ageNode.nodeValue, 10);
        
        // Return the student information object
        return {
            name: nameNode.nodeValue,
            citizenship: citizenshipNode.nodeValue,
            age: isNaN(age) ? null : age
        };
    } catch (error) {
        // In case of any parsing or XPath errors, return null
        return null;
    }
}