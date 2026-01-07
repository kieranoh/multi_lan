package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo parses XML data and returns student information for the given username and password.
// @param xmlData XML data containing student information.
// @param username The username of the student being searched for.
// @param password The password of the student being searched for.
// @return Tuple (name, age, citizenship) if the student is found. Otherwise returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create a new XML tree from the data
	xmlReader := strings.NewReader(xmlData)
	tree, err := xmltree.Parse(xmlReader)
	if err != nil {
		return "", "", ""
	}

	// Create a new XPath navigator
	navigator := goxpath.NewNavigator(tree)

	// Construct XPath query to find the student
	xpathQuery := fmt.Sprintf("//student[username='%s' and password='%s']", username, password)

	// Evaluate the XPath query
	result, err := navigator.Query(xpathQuery)
	if err != nil || result.Count() == 0 {
		return "", "", ""
	}

	// Extract the student information
	var name, age, citizenship string
	for result.Next() {
		name = result.Current().Select("name").String()
		age = result.Current().Select("age").String()
		citizenship = result.Current().Select("citizenship").String()
	}

	return name, age, citizenship
}