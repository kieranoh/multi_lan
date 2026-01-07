package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

// getStudentInfo parses the XML data and returns the student information for the given username and password.
// If the student is found, it returns a tuple (name, age, citizenship). Otherwise, it returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create a new XML tree from the provided XML data
	reader := strings.NewReader(xmlData)
	xmlTree, err := xmltree.Parse(reader)
	if err != nil {
		return "", "", ""
	}

	// Create an XPath navigator
	navigator := goxpath.NewNavigator(xmlTree)

	// Construct the XPath query to find the student with the specified username and password
	xpathQuery := "//student[username='" + username + "' and password='" + password + "']"

	// Execute the XPath query
	if err := navigator.Select(xpathQuery); err != nil {
		return "", "", ""
	}

	// Get the selected student element
	if navigator.MoveNext() {
		studentNode := navigator.Current()

		// Extract name, age, and citizenship from the student element
		name := getNodeValue(studentNode, "name")
		age := getNodeValue(studentNode, "age")
		citizenship := getNodeValue(studentNode, "citizenship")

		return name, age, citizenship
	}

	return "", "", ""
}

// getNodeValue retrieves the text value of a child node with the given name
func getNodeValue(node tree.Node, childName string) string {
	for _, child := range node.Children() {
		if child.Name() == childName {
			if textNode, ok := child.(*xmltree.Element); ok {
				return textNode.Text()
			}
		}
	}
	return ""
}