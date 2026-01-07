package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo parses the XML data and returns the student information for the given username and password.
// The XML data is structured as follows:
// <students>
//     <student>
//         <username>john_doe</username>
//         <password>jdpassword</password>
//         <name>John Doe</name>
//         <citizenship>USA</citizenship>
//         <age>25</age>
//     </student>
//     <student>
//         <username>bob_smith</username>
//         <password>bspassword</password>
//         <name>Bob Smith</name>
//         <citizenship>Canada</citizenship>
//         <age>22</age>
//     </student>
// </students>
//
// @param xmlData The XML data containing student information.
// @param username The username of the student to search for.
// @param password The password of the student to search for.
//
// @return A tuple (name, age, citizenship) if the student is found, otherwise returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create an XML tree from the provided XML data
	xmlNode, err := xmltree.ParseString(xmlData)
	if err != nil {
		return "", "", ""
	}

	// Create a new XPath navigator for the XML tree
	navigator := goxpath.NewNavigator(xmlNode)

	// Create the XPath query to find the student with the specified username and password
	query := fmt.Sprintf("//student[username='%s' and password='%s']", username, password)

	// Execute the XPath query
	if results, err := navigator.Query(query); err == nil && results != nil {
		for results.Next() {
			// Extract student information
			name := results.Current().Select("name").String()
			age := results.Current().Select("age").String()
			citizenship := results.Current().Select("citizenship").String()
			return name, age, citizenship
		}
	}
	return "", "", ""
}