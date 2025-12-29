package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

// getStudentInfo parses the XML data and returns student information for the given username and password.
// It returns a tuple (name, age, citizenship) if the student is found, otherwise it returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create a new XML tree from the provided XML data
	reader := strings.NewReader(xmlData)
	tree, err := xmltree.Parse(reader)
	if err != nil {
		return "", "", ""
	}

	// Create a new XPath navigator
	navigator := goxpath.NewNavigator(tree)

	// Construct the XPath query to find the student with the given username and password
	xpathQuery := "//student[username='" + username + "' and password='" + password + "']"

	// Execute the XPath query
	result, err := navigator.Select(xpathQuery)
	if err != nil || result.Count() == 0 {
		return "", "", ""
	}

	// Extract the required information from the result
	var name, age, citizenship string

	// Iterate over the result to retrieve name, age, and citizenship
	for result.Next() {
		name = result.Current().Select("name").String()
		age = result.Current().Select("age").String()
		citizenship = result.Current().Select("citizenship").String()
	}

	return name, age, citizenship
}