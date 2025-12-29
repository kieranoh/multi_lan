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

	// Construct XPath query to find student with matching username and password
	xpathQuery := "/students/student[username='" + username + "' and password='" + password + "']"

	// Execute XPath query
	xpExec := goxpath.MustParse(xpathQuery)
	res, err := xpExec.Exec(xmlTree, tree.NavigatorOptions{})
	if err != nil {
		return "", "", ""
	}

	// Check if any results were found
	if len(res) == 0 {
		return "", "", ""
	}

	// Get the first matching student node
	studentNode := res[0]

	// Extract name, age, and citizenship using XPath
	nameXPath := goxpath.MustParse("name")
	ageXPath := goxpath.MustParse("age")
	citizenshipXPath := goxpath.MustParse("citizenship")

	nameRes, err := nameXPath.Exec(studentNode, tree.NavigatorOptions{})
	if err != nil || len(nameRes) == 0 {
		return "", "", ""
	}

	ageRes, err := ageXPath.Exec(studentNode, tree.NavigatorOptions{})
	if err != nil || len(ageRes) == 0 {
		return "", "", ""
	}

	citizenshipRes, err := citizenshipXPath.Exec(studentNode, tree.NavigatorOptions{})
	if err != nil || len(citizenshipRes) == 0 {
		return "", "", ""
	}

	// Convert results to strings
	name := tree.String(nameRes[0])
	age := tree.String(ageRes[0])
	citizenship := tree.String(citizenshipRes[0])

	return name, age, citizenship
}