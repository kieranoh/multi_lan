package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo parses the given XML data and returns student information for the provided username and password.
// If the student is found, it returns a tuple (name, age, citizenship). Otherwise, it returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse the XML data
	reader := strings.NewReader(xmlData)
	root, err := xmltree.Parse(reader)
	if err != nil {
		return "", "", ""
	}

	// Create an XPath query to find the student by username and password
	query := fmt.Sprintf("//student[username='%s' and password='%s']", username, password)
	nodes, err := goxpath.Query(root, query)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	// Extract the name, age, and citizenship
	name := goxpath.StringValue(nodes[0].SelectChild("name"))
	age := goxpath.StringValue(nodes[0].SelectChild("age"))
	citizenship := goxpath.StringValue(nodes[0].SelectChild("citizenship"))

	return name, age, citizenship
}