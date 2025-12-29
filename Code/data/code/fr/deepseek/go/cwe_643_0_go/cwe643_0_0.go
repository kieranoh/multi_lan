package main

import (
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse the XML data
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Build XPath query to find student with matching username and password
	xpathQuery := "/students/student[username='" + username + "' and password='" + password + "']"

	// Execute the XPath query
	xpExec := goxpath.MustParse(xpathQuery)
	res, err := xpExec.Exec(tree.Node(xmlTree))
	if err != nil {
		return "", "", ""
	}

	// Check if we found a student
	nodes, ok := res.(tree.NodeSet)
	if !ok || len(nodes) == 0 {
		return "", "", ""
	}

	// Get the first matching student node
	studentNode := nodes[0]

	// Extract name, age, and citizenship using XPath
	nameQuery := goxpath.MustParse("name/text()")
	ageQuery := goxpath.MustParse("age/text()")
	citizenshipQuery := goxpath.MustParse("citizenship/text()")

	nameRes, err := nameQuery.Exec(tree.Node(studentNode))
	if err != nil {
		return "", "", ""
	}
	ageRes, err := ageQuery.Exec(tree.Node(studentNode))
	if err != nil {
		return "", "", ""
	}
	citizenshipRes, err := citizenshipQuery.Exec(tree.Node(studentNode))
	if err != nil {
		return "", "", ""
	}

	// Convert results to strings
	name := ""
	if nameNodes, ok := nameRes.(tree.NodeSet); ok && len(nameNodes) > 0 {
		if str, ok := nameNodes[0].(tree.String); ok {
			name = string(str)
		}
	}

	age := ""
	if ageNodes, ok := ageRes.(tree.NodeSet); ok && len(ageNodes) > 0 {
		if str, ok := ageNodes[0].(tree.String); ok {
			age = string(str)
		}
	}

	citizenship := ""
	if citizenshipNodes, ok := citizenshipRes.(tree.NodeSet); ok && len(citizenshipNodes) > 0 {
		if str, ok := citizenshipNodes[0].(tree.String); ok {
			citizenship = string(str)
		}
	}

	return name, age, citizenship
}