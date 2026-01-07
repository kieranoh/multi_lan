package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo parses XML data and returns the student information for the given username and password.
// XML data is expected to be structured as follows:
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
// @return A tuple of (name, age, citizenship) if the student is found, otherwise an empty string.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	root, err := xmltree.ParseString(xmlData)
	if err != nil {
		return "", "", ""
	}

	xpath, err := goxpath.Compile("//student[username='" + username + "' and password='" + password + "']")
	if err != nil {
		return "", "", ""
	}

	nodes, err := xpath.Evaluate(root)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	if studentNode, ok := nodes[0].(*tree.Node); ok {
		nameNode := studentNode.Select("name")
		ageNode := studentNode.Select("age")
		citizenshipNode := studentNode.Select("citizenship")

		name := ""
		age := ""
		citizenship := ""

		if nameNode != nil {
			name = nameNode.Content()
		}
		if ageNode != nil {
			age = ageNode.Content()
		}
		if citizenshipNode != nil {
			citizenship = citizenshipNode.Content()
		}

		return name, age, citizenship
	}

	return "", "", ""
}