package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo parses the provided XML data and returns the student information 
// for the given username and password. It returns the name, age, and citizenship 
// of the student if found, otherwise it returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse the XML data
	doc, err := xmltree.Parse([]byte(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Create an XPath expression to find the student with the given username and password
	xpathExpr := fmt.Sprintf("//student[username='%s' and password='%s']", username, password)
	studentNodes, err := goxpath.Evaluate(xpathExpr, doc)
	if err != nil || len(studentNodes) == 0 {
		return "", "", ""
	}

	// Extract the information
	studentNode := studentNodes[0]
	name := studentNode.Select("name").Text()
	age := studentNode.Select("age").Text()
	citizenship := studentNode.Select("citizenship").Text()

	return name, age, citizenship
}