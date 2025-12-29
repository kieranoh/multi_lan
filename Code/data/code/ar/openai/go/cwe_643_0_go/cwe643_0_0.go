package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo parses the XML data and retrieves the student's information based on the given username and password.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse the XML data
	doc, err := xmltree.Parse([]byte(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Create a new XPath navigator
	navigator := goxpath.NewNavigator(doc)

	// Construct XPath query to find the student with the given username and password
	query := fmt.Sprintf("//student[username='%s' and password='%s']", username, password)

	// Execute the XPath query
	if err := navigator.Select(query); err != nil {
		return "", "", ""
	}

	// Retrieve the information if a student is found
	if navigator.Current() != nil {
		name := navigator.Current().SelectSingle("name").Text()
		age := navigator.Current().SelectSingle("age").Text()
		citizenship := navigator.Current().SelectSingle("citizenship").Text()
		return name, age, citizenship
	}

	return "", "", ""
}