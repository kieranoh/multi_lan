package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo parses the XML data and returns the student's information based on the provided username and password.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse the XML data
	reader := strings.NewReader(xmlData)
	doc, err := xmltree.Parse(reader)
	if err != nil {
		return "", "", ""
	}

	// Create an XPath navigator
	navigator := goxpath.NewXPathNavigator(doc)

	// Construct the XPath query to find the student by username and password
	xpathQuery := fmt.Sprintf("//student[username='%s' and password='%s']", username, password)

	// Execute the XPath query
	if result, err := navigator.Select(xpathQuery); err == nil && result.Next() {
		// Extract student details
		name := result.Current().SelectValue("name")
		age := result.Current().SelectValue("age")
		citizenship := result.Current().SelectValue("citizenship")

		return name, age, citizenship
	}

	return "", "", ""
}