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

	// Construct XPath query to find the student with given username and password
	xpathQuery := "/students/student[username='" + username + "' and password='" + password + "']"

	// Execute the XPath query
	xpExec := goxpath.MustParse(xpathQuery)
	res, err := xpExec.Exec(xmlTree, tree.NsMap{})
	if err != nil {
		return "", "", ""
	}

	// Check if any result was found
	nodes, ok := res.(tree.NodeSet)
	if !ok || len(nodes) == 0 {
		return "", "", ""
	}

	// Get the first matching student node
	studentNode := nodes[0]

	// Extract name, age, and citizenship using XPath
	nameXPath := goxpath.MustParse("name/text()")
	ageXPath := goxpath.MustParse("age/text()")
	citizenshipXPath := goxpath.MustParse("citizenship/text()")

	nameRes, err := nameXPath.Exec(studentNode, tree.NsMap{})
	if err != nil {
		return "", "", ""
	}
	ageRes, err := ageXPath.Exec(studentNode, tree.NsMap{})
	if err != nil {
		return "", "", ""
	}
	citizenshipRes, err := citizenshipXPath.Exec(studentNode, tree.NsMap{})
	if err != nil {
		return "", "", ""
	}

	// Convert results to strings
	name := ""
	if nameNodes, ok := nameRes.(tree.NodeSet); ok && len(nameNodes) > 0 {
		if textNode, ok := nameNodes[0].(tree.Text); ok {
			name = string(textNode)
		}
	}

	age := ""
	if ageNodes, ok := ageRes.(tree.NodeSet); ok && len(ageNodes) > 0 {
		if textNode, ok := ageNodes[0].(tree.Text); ok {
			age = string(textNode)
		}
	}

	citizenship := ""
	if citizenshipNodes, ok := citizenshipRes.(tree.NodeSet); ok && len(citizenshipNodes) > 0 {
		if textNode, ok := citizenshipNodes[0].(tree.Text); ok {
			citizenship = string(textNode)
		}
	}

	return name, age, citizenship
}