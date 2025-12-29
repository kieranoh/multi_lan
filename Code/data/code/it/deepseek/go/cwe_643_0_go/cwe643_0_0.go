package main

import (
	"errors"
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

	// Helper function to extract text content from a child element
	getChildText := func(parent tree.Node, childName string) (string, error) {
		xpath := childName
		xpChild := goxpath.MustParse(xpath)
		childRes, err := xpChild.Exec(tree.Node(parent))
		if err != nil {
			return "", err
		}

		childNodes, ok := childRes.(tree.NodeSet)
		if !ok || len(childNodes) == 0 {
			return "", errors.New("child not found")
		}

		// Get text content
		textNodes := childNodes[0].GetChildren()
		if len(textNodes) == 0 {
			return "", errors.New("no text content")
		}

		textNode, ok := textNodes[0].(tree.Char)
		if !ok {
			return "", errors.New("not a text node")
		}

		return string(textNode), nil
	}

	// Extract name, age, and citizenship
	name, err := getChildText(studentNode, "name")
	if err != nil {
		name = ""
	}

	age, err := getChildText(studentNode, "age")
	if err != nil {
		age = ""
	}

	citizenship, err := getChildText(studentNode, "citizenship")
	if err != nil {
		citizenship = ""
	}

	return name, age, citizenship
}