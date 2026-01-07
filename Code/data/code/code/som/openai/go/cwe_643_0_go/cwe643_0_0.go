package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo parses the XML data and returns student information for the given username and password.
// XML data has the following structure:
// <students>
//     <student>
//         <username>john_doe</username>
//         <password>jdpassword</password>
//         <name>John Doe</name>
//         <citizenship>USA</citizenship>
//         <age>25</age>
//     </student>
//     ...
// </students>
//
// @param xmlData Contains student information in XML format.
// @param username The username of the student to search for.
// @param password The password of the student to search for.
//
// @return A tuple of (name, age, citizenship) if the student is found; otherwise returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	doc, err := xmltree.ParseString(xmlData)
	if err != nil {
		return "", "", ""
	}

	xpath := goxpath.MustCompile(fmt.Sprintf("//student[username='%s' and password='%s']", username, password))
	nodes := xpath.Select(doc)

	if len(nodes) == 0 {
		return "", "", ""
	}

	name := nodes[0].Select("//name")[0].Value()
	age := nodes[0].Select("//age")[0].Value()
	citizenship := nodes[0].Select("//citizenship")[0].Value()

	return name, age, citizenship
}