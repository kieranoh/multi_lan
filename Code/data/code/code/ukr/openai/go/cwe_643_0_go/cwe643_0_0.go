package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo parses the provided XML data and returns the student information for the given username and password.
// It returns a tuple of (name, age, citizenship) if the student is found, otherwise returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create a new XML tree from the XML data
	xmlTree, err := xmltree.Parse(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Create a new XPath navigator
	navigator := goxpath.NewNavigator(xmlTree)

	// Create the XPath query to find the student by username and password
	query := "//student[username='" + username + "' and password='" + password + "']"

	// Evaluate the query
	nodes, err := navigator.Select(query)
	if err != nil {
		return "", "", ""
	}

	// Check if we found any students
	if nodes.MoveNext() {
		studentNode := nodes.Current()
		name := studentNode.SelectSingleNode("name").Value()
		age := studentNode.SelectSingleNode("age").Value()
		citizenship := studentNode.SelectSingleNode("citizenship").Value()
		return name, age, citizenship
	}

	// If no student found, return empty strings
	return "", "", ""
}