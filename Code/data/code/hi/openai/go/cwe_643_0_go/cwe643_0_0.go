package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo parses XML data and returns the student's information for the given username and password.
// @param xmlData: XML data containing student information.
// @param username: The username of the student to search for.
// @param password: The password of the student to search for.
// @return: A tuple of (name, age, citizenship) if the student is found, otherwise returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse the XML data
	root, err := xmltree.Parse(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Create an XPath selector
	xpath := goxpath.NewXPath(root)

	// Create an XPath query to find the student by username and password
	query := "//student[username='" + username + "' and password='" + password + "']"

	// Evaluate the XPath query
	nodes, err := xpath.Select(query)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	// Extract student information
	name := nodes[0].SelectSingleNode("name").Value()
	age := nodes[0].SelectSingleNode("age").Value()
	citizenship := nodes[0].SelectSingleNode("citizenship").Value()

	return name, age, citizenship
}