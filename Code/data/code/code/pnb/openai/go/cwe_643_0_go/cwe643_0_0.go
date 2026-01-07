package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo parses the given XML data and returns student information 
// for the provided username and password.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse the XML data
	doc, err := xmltree.ParseString(xmlData)
	if err != nil {
		return "", "", ""
	}

	// Create an XPath navigator
	navigator := goxpath.NewNavigator(doc)

	// Define the XPath query to find the student by username and password
	query := fmt.Sprintf("//student[username='%s' and password='%s']", username, password)

	// Execute the query
	result, err := navigator.Select(query)
	if err != nil || result.Count() == 0 {
		return "", "", ""
	}

	// Extract the student's name, age, and citizenship
	name := result.Node().Select("name").String()
	age := result.Node().Select("age").String()
	citizenship := result.Node().Select("citizenship").String()

	return name, age, citizenship
}