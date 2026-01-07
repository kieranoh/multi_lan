package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
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
//     ...
// </students>
//
// @param xmlData The XML data containing student information.
// @param username The username of the student to search for.
// @param password The password of the student to search for.
//
// @return A tuple of (name, age, citizenship) if a student is found, otherwise an empty string.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	doc, err := xmltree.Parse(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	xpath := goxpath.NewXPath(doc)

	query := fmt.Sprintf("//student[username='%s' and password='%s']", username, password)
	nodes, err := xpath.Query(query)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	name := xpath.QuerySingle("//student[username='%s']/name", username).String()
	age := xpath.QuerySingle("//student[username='%s']/age", username).String()
	citizenship := xpath.QuerySingle("//student[username='%s']/citizenship", username).String()

	return name, age, citizenship
}