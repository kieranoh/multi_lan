package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo parses the XML data and returns the student information for the given username and password.
// If the student is found, it returns a tuple (name, age, citizenship). Otherwise, it returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create a new XML tree from the provided XML data
	xmlNode, err := xmltree.Parse(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Create a new XPath expression to find the student with the given username and password
	xpathExpr := "//student[username='" + username + "' and password='" + password + "']"

	// Create a new XPath query
	query, err := goxpath.Compile(xpathExpr)
	if err != nil {
		return "", "", ""
	}

	// Evaluate the XPath query against the XML tree
	results := query.Evaluate(xmlNode)
	if results == nil || len(results) == 0 {
		return "", "", ""
	}

	// Extract the student information
	student := results[0].(*tree.Node)
	name := student.GetChild("name").Content()
	age := student.GetChild("age").Content()
	citizenship := student.GetChild("citizenship").Content()

	return name, age, citizenship
}