package main

import (
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo parses XML data and returns student information for the given username and password.
// XML data has the following structure:
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
// @param username Username of the student to search for.
// @param password Password of the student to search for.
//
// @return If student is found, returns (name, age, citizenship) tuple. Otherwise returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse XML data
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Create XPath expression to find student with matching username and password
	xpathExpr := goxpath.MustParse(
		"/students/student[username='" + username + "' and password='" + password + "']",
	)

	// Execute XPath query
	result, err := xpathExpr.ExecNode(xmlTree)
	if err != nil {
		return "", "", ""
	}

	// Check if we found a matching student
	if len(result) == 0 {
		return "", "", ""
	}

	// Get the student node
	studentNode := result[0]

	// Extract name, age, and citizenship using XPath
	nameExpr := goxpath.MustParse("name")
	ageExpr := goxpath.MustParse("age")
	citizenshipExpr := goxpath.MustParse("citizenship")

	nameNodes, _ := nameExpr.ExecNode(tree.Node(studentNode))
	ageNodes, _ := ageExpr.ExecNode(tree.Node(studentNode))
	citizenshipNodes, _ := citizenshipExpr.ExecNode(tree.Node(studentNode))

	// Helper function to extract text from nodes
	extractText := func(nodes []tree.Node) string {
		if len(nodes) == 0 {
			return ""
		}
		if elem, ok := nodes[0].(tree.Elem); ok {
			return elem.ResValue()
		}
		return ""
	}

	name := extractText(nameNodes)
	age := extractText(ageNodes)
	citizenship := extractText(citizenshipNodes)

	return name, age, citizenship
}