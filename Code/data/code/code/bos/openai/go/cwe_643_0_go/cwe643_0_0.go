package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo parses XML data and returns student information for the given username and password.
// If the student is found, it returns a tuple (name, age, citizenship). Otherwise, it returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create a new XML tree from the provided XML data
	root, err := xmltree.ParseString(xmlData)
	if err != nil {
		return "", "", ""
	}

	// Construct the XPath query to find the student with the given username and password
	query := "//student[username='" + username + "' and password='" + password + "']"

	// Execute the XPath query
	nodes, err := goxpath.Select(query, root)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	// Extract the name, age, and citizenship of the found student
	name := nodes[0].Select("name").Text()
	age := nodes[0].Select("age").Text()
	citizenship := nodes[0].Select("citizenship").Text()

	return name, age, citizenship
}