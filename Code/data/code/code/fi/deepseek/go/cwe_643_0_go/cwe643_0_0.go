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
	xpathExpr := goxpath.MustParse(
		"/students/student[username='" + username + "' and password='" + password + "']",
	)

	// Execute the XPath query
	result, err := xpathExpr.ExecNode(xmlTree)
	if err != nil {
		return "", "", ""
	}

	// Check if we found a matching student
	if len(result) == 0 {
		return "", "", ""
	}

	// Get the first matching student node
	studentNode := result[0]

	// Extract name, age, and citizenship using XPath
	nameExpr := goxpath.MustParse("name/text()")
	ageExpr := goxpath.MustParse("age/text()")
	citizenshipExpr := goxpath.MustParse("citizenship/text()")

	nameResult, err := nameExpr.ExecNode(tree.Node(studentNode))
	if err != nil || len(nameResult) == 0 {
		return "", "", ""
	}

	ageResult, err := ageExpr.ExecNode(tree.Node(studentNode))
	if err != nil || len(ageResult) == 0 {
		return "", "", ""
	}

	citizenshipResult, err := citizenshipExpr.ExecNode(tree.Node(studentNode))
	if err != nil || len(citizenshipResult) == 0 {
		return "", "", ""
	}

	// Convert results to strings
	name := nameResult[0].(tree.Elem).ResValue()
	age := ageResult[0].(tree.Elem).ResValue()
	citizenship := citizenshipResult[0].(tree.Elem).ResValue()

	return name, age, citizenship
}