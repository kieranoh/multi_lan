package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo parses the XML data and returns student information for the given username and password.
// The XML data has the following structure:
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
// @param xmlData XML data containing student information.
// @param username The username of the student to search for.
// @param password The password of the student to search for.
//
// @return A tuple (name, age, citizenship) if the student is found, otherwise an empty string.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse the XML data
	root, err := xmltree.ParseString(xmlData)
	if err != nil {
		return "", "", ""
	}

	// Create an XPath evaluator
	evaluator := goxpath.NewEvaluator(root)

	// Construct the XPath query
	query := fmt.Sprintf("//student[username='%s' and password='%s']", username, password)

	// Execute the XPath query
	nodes, err := evaluator.Query(query)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	// Extract student information
	name := nodes[0].SelectChild("name").Text()
	age := nodes[0].SelectChild("age").Text()
	citizenship := nodes[0].SelectChild("citizenship").Text()

	return name, age, citizenship
}