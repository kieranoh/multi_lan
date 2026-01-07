package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo parses the XML data and returns the student information for the given username and password.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create a new XML tree from the provided XML data
	xmlReader := xmltree.NewReader(strings.NewReader(xmlData))
	tree, err := tree.New(xmlReader)
	if err != nil {
		return "", "", ""
	}

	// Create a new XPath evaluator
	evaluator := goxpath.NewEvaluator(tree)

	// Prepare the XPath query to find the student with the given username and password
	query := fmt.Sprintf("//student[username='%s' and password='%s']", username, password)

	// Evaluate the XPath query
	nodes, err := evaluator.Evaluate(query)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	// Extract student information
	name := nodes[0].SelectNode("//name").String()
	age := nodes[0].SelectNode("//age").String()
	citizenship := nodes[0].SelectNode("//citizenship").String()

	return name, age, citizenship
}