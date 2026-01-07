package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo parses the XML data and returns the student information for the given username and password.
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
// @param username The username of the student to search for.
// @param password The password of the student to search for.
//
// @return A tuple (name, age, citizenship) if the student is found. Otherwise, it returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	doc := xmltree.NewDocument([]byte(xmlData))
	xpath := goxpath.MustCompile("//student[username='" + username + "' and password='" + password + "']")

	nodes := xpath.Select(doc)
	if len(nodes) > 0 {
		name := nodes[0].SelectChild("name").Text()
		age := nodes[0].SelectChild("age").Text()
		citizenship := nodes[0].SelectChild("citizenship").Text()
		return name, age, citizenship
	}

	return "", "", ""
}