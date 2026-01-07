package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo parses the XML data and returns the student information for the given username and password.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create a new XML tree from the provided XML data
	xmlDoc, err := xmltree.Parse(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Create a new XPath
	xpath := goxpath.NewXPath(xmlDoc)

	// Construct the XPath query to find the student by username and password
	query := "//student[username='" + username + "' and password='" + password + "']"

	// Execute the XPath query
	nodes, err := xpath.Select(query)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	// Extract information if a student is found
	studentNode := nodes[0]
	name := studentNode.SelectSingleNode("name").Text()
	age := studentNode.SelectSingleNode("age").Text()
	citizenship := studentNode.SelectSingleNode("citizenship").Text()

	return name, age, citizenship
}