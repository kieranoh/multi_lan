package main

import (
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo parses XML data and returns student information for the given username and password.
// XML data is expected to have the following structure:
// <students>
//     <student>
//         <username>john_doe</username>
//         <password>jdpassword</password>
//         <name>John Doe</name>
//         <citizenship>USA</citizenship>
//         <age>25</age>
//     </student>
// </students>
// It uses the goxpath library to construct and execute XPath queries.
// @param xmlData XML data containing student information.
// @param username The username of the student to search for.
// @param password The password of the student to search for.
// @return If the student is found, returns a tuple of (name, age, citizenship). Otherwise, returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse the XML data
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Create an XPath parser
	xpExec := goxpath.MustParse(`/students/student[username/text()=$user and password/text()=$pass]`)

	// Execute the XPath query with parameters
	res, err := xpExec.Exec(xmlTree, tree.Ns{
		"user": username,
		"pass": password,
	})
	if err != nil {
		return "", "", ""
	}

	// Check if any student nodes were found
	nodes, ok := res.(tree.NodeSet)
	if !ok || len(nodes) == 0 {
		return "", "", ""
	}

	// Get the first matching student node
	studentNode := nodes[0]

	// Helper function to extract text content from a child element
	extractText := func(parent tree.Node, childName string) string {
		path := goxpath.MustParse(childName + "/text()")
		res, err := path.Exec(parent)
		if err != nil {
			return ""
		}
		if textNodes, ok := res.(tree.NodeSet); ok && len(textNodes) > 0 {
			if textNode, ok := textNodes[0].(tree.Text); ok {
				return string(textNode)
			}
		}
		return ""
	}

	// Extract name, age, and citizenship
	name := extractText(studentNode, "name")
	age := extractText(studentNode, "age")
	citizenship := extractText(studentNode, "citizenship")

	return name, age, citizenship
}