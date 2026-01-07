package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

// getStudentInfo parses the XML data and returns student information for the given username and password.
// If the student is found, it returns a tuple (name, age, citizenship). Otherwise, it returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse the XML data
	reader := strings.NewReader(xmlData)
	decoder := xml.NewDecoder(reader)
	
	// Create a new XML tree
	xmlTree, err := xmltree.New(decoder)
	if err != nil {
		return "", "", ""
	}

	// Create an XPath query to find the student node with the given username and password
	query := "//student[username='" + username + "' and password='" + password + "']"

	// Evaluate the XPath query
	nodes, err := goxpath.Select(xmlTree, query)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	// Extract information from the found node
	studentNode := nodes[0]
	name := goxpath.SelectSingle(studentNode, "name")
	age := goxpath.SelectSingle(studentNode, "age")
	citizenship := goxpath.SelectSingle(studentNode, "citizenship")

	return name.Text(), age.Text(), citizenship.Text()
}