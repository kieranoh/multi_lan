package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo parses the XML data and returns the student information 
// for the specified username and password.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create a new XML tree from the provided XML data
	xmlNode, err := xmltree.New([]byte(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Create a new XPath object
	xpathObj := goxpath.New(xmlNode)

	// Build the XPath query for the student with the specified username and password
	xpathQuery := fmt.Sprintf("//student[username='%s' and password='%s']", username, password)

	// Execute the XPath query
	result, err := xpathObj.Query(xpathQuery)
	if err != nil || len(result) == 0 {
		return "", "", ""
	}

	// Extract the name, age, and citizenship from the result
	studentNode := result[0]
	name := studentNode.SelectChild("name").String()
	age := studentNode.SelectChild("age").String()
	citizenship := studentNode.SelectChild("citizenship").String()

	return name, age, citizenship
}