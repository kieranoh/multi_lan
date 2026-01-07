package main

import (
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse XML data
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Build XPath query to find student with matching username and password
	xpathQuery := goxpath.MustParse(
		"/students/student[username='" + username + "' and password='" + password + "']",
	)

	// Execute XPath query
	result, err := xpathQuery.ExecNode(xmlTree)
	if err != nil {
		return "", "", ""
	}

	// Check if student was found
	if len(result) == 0 {
		return "", "", ""
	}

	// Get the student node
	studentNode := result[0]

	// Extract name, age, and citizenship using XPath
	nameXPath := goxpath.MustParse("name/text()")
	ageXPath := goxpath.MustParse("age/text()")
	citizenshipXPath := goxpath.MustParse("citizenship/text()")

	nameRes, _ := nameXPath.ExecNode(studentNode.(tree.Node))
	ageRes, _ := ageXPath.ExecNode(studentNode.(tree.Node))
	citizenshipRes, _ := citizenshipXPath.ExecNode(studentNode.(tree.Node))

	// Convert results to strings
	name := ""
	if len(nameRes) > 0 {
		name = tree.String(nameRes[0])
	}

	age := ""
	if len(ageRes) > 0 {
		age = tree.String(ageRes[0])
	}

	citizenship := ""
	if len(citizenshipRes) > 0 {
		citizenship = tree.String(citizenshipRes[0])
	}

	return name, age, citizenship
}