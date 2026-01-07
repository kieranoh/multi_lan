package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

// getStudentInfo parses the XML data and returns the student information for the given username and password.
// If the student is found, it returns a tuple of (name, age, citizenship). Otherwise, it returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create a new XML tree
	root, err := xmltree.Parse(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Create an XPath evaluator
	evaluator := goxpath.NewEvaluator(root)

	// XPath query to find the student with the provided username and password
	query := "//student[username='" + username + "' and password='" + password + "']"

	// Execute the XPath query
	nodes, err := evaluator.Query(query)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	// Extract the student information
	studentNode := nodes[0]
	name := getNodeValue(studentNode, "name")
	age := getNodeValue(studentNode, "age")
	citizenship := getNodeValue(studentNode, "citizenship")

	return name, age, citizenship
}

// getNodeValue retrieves the text value of a child node with the given name.
func getNodeValue(node tree.Node, childName string) string {
	children := node.Children()
	for _, child := range children {
		if child.Name() == childName {
			return child.Value()
		}
	}
	return ""
}