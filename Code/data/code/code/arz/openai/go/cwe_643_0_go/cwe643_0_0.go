package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"bytes"
)

// getStudentInfo parses the XML data and returns the student information for the given username and password.
// If the student is found, it returns (name, age, citizenship) tuple. Otherwise, it returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create a new XML tree from the provided XML data
	reader := bytes.NewReader([]byte(xmlData))
	decoder := xml.NewDecoder(reader)
	tree, err := xmltree.New(decoder)
	if err != nil {
		return "", "", ""
	}

	// Create an XPath expression to find the student by username and password
	xpathExpr := "//student[username='" + username + "' and password='" + password + "']"

	// Evaluate the XPath expression to find the student node
	students, err := goxpath.Eval(tree, xpathExpr)
	if err != nil || len(students) == 0 {
		return "", "", ""
	}

	// Extract the information from the found student node
	studentNode := students[0]
	name := studentNode.SelectSingleNode("name").Content
	age := studentNode.SelectSingleNode("age").Content
	citizenship := studentNode.SelectSingleNode("citizenship").Content

	return name, age, citizenship
}