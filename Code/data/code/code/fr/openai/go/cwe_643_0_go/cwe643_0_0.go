package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo analyses the XML data and returns the student information for the given username and password.
// It returns a tuple (name, age, citizenship) if the student is found. Otherwise, it returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse the XML data
	root, err := xmltree.ParseString(xmlData)
	if err != nil {
		return "", "", ""
	}

	// Create an XPath navigator
	navigator := goxpath.NewNavigator(root)

	// Define the XPath expression to find the student by username and password
	xpathExpr := "//student[username='" + username + "' and password='" + password + "']"

	// Find the matching student node
	if err := navigator.Select(xpathExpr); err != nil {
		return "", "", ""
	}

	// If a student node is found, extract the required information
	if navigator.Current() != nil {
		name := navigator.Current().SelectSingle("name").Text()
		age := navigator.Current().SelectSingle("age").Text()
		citizenship := navigator.Current().SelectSingle("citizenship").Text()
		return name, age, citizenship
	}

	// Return empty strings if no student was found
	return "", "", ""
}