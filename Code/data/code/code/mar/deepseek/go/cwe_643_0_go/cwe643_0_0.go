package main

import (
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo parses XML data and returns student information for the given username and password.
// XML data structure:
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
// @return If student is found, returns a tuple of (name, age, citizenship). Otherwise returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse the XML data
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Create XPath query to find student with matching username and password
	xpathQuery := "/students/student[username='" + username + "' and password='" + password + "']"
	
	// Execute the XPath query
	xpExec := goxpath.MustParse(xpathQuery)
	res, err := xpExec.Exec(tree.Node(xmlTree))
	if err != nil {
		return "", "", ""
	}

	// Check if any results were found
	nodes := res.(tree.NodeSet)
	if len(nodes) == 0 {
		return "", "", ""
	}

	// Get the first matching student node
	studentNode := nodes[0]

	// Extract name, age, and citizenship using XPath
	nameQuery := goxpath.MustParse("name/text()")
	ageQuery := goxpath.MustParse("age/text()")
	citizenshipQuery := goxpath.MustParse("citizenship/text()")

	nameRes, err := nameQuery.Exec(tree.Node(studentNode))
	if err != nil {
		return "", "", ""
	}

	ageRes, err := ageQuery.Exec(tree.Node(studentNode))
	if err != nil {
		return "", "", ""
	}

	citizenshipRes, err := citizenshipQuery.Exec(tree.Node(studentNode))
	if err != nil {
		return "", "", ""
	}

	// Convert results to strings
	name := ""
	if nameNodes, ok := nameRes.(tree.NodeSet); ok && len(nameNodes) > 0 {
		if strNode, ok := nameNodes[0].(tree.String); ok {
			name = string(strNode)
		}
	}

	age := ""
	if ageNodes, ok := ageRes.(tree.NodeSet); ok && len(ageNodes) > 0 {
		if strNode, ok := ageNodes[0].(tree.String); ok {
			age = string(strNode)
		}
	}

	citizenship := ""
	if citizenshipNodes, ok := citizenshipRes.(tree.NodeSet); ok && len(citizenshipNodes) > 0 {
		if strNode, ok := citizenshipNodes[0].(tree.String); ok {
			citizenship = string(strNode)
		}
	}

	return name, age, citizenship
}