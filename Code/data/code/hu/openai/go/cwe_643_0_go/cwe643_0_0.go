package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo parses the XML data and returns the student information 
// based on the provided username and password. The XML data has the following structure:
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
// @return A tuple (name, age, citizenship) if the student is found. 
//         Otherwise, returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	reader := strings.NewReader(xmlData)
	tree, err := xmltree.Parse(reader)
	if err != nil {
		return "", "", ""
	}

	xpath := goxpath.NewXPath(tree)

	query := "//student[username='" + username + "' and password='" + password + "']"
	results, err := xpath.Query(query)
	if err != nil || len(results) == 0 {
		return "", "", ""
	}

	var name, age, citizenship string

	for _, node := range results {
		nameNode := node.Select("name")
		ageNode := node.Select("age")
		citizenshipNode := node.Select("citizenship")

		if nameNode != nil {
			name = nameNode.Text()
		}
		if ageNode != nil {
			age = ageNode.Text()
		}
		if citizenshipNode != nil {
			citizenship = citizenshipNode.Text()
		}
	}

	return name, age, citizenship
}