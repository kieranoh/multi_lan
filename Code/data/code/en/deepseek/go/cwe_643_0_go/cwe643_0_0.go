package main

import (
	"errors"
	"fmt"
	"strconv"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo parses the XML data and returns the student information for the given username and password.
// It returns a tuple (name, age, citizenship) if the student is found, otherwise returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse the XML data
	xmlTree, err := xmltree.ParseXML(xmlData)
	if err != nil {
		// Return empty strings if parsing fails
		return "", "", ""
	}

	// Construct XPath query to find the student with matching username and password
	xpathQuery := fmt.Sprintf(
		"/students/student[username='%s' and password='%s']",
		username,
		password,
	)

	// Compile the XPath expression
	xpExec := goxpath.MustParse(xpathQuery)

	// Execute the query
	res, err := xpExec.ExecNode(xmlTree)
	if err != nil {
		// Return empty strings if query execution fails
		return "", "", ""
	}

	// Check if we found a matching student
	if res == nil || len(res) == 0 {
		return "", "", ""
	}

	// We expect exactly one matching student node
	studentNode := res[0]

	// Helper function to extract text content from a child element
	extractText := func(parent tree.Node, childName string) (string, error) {
		// Construct XPath to get the child element text
		childXPath := goxpath.MustParse(childName + "/text()")
		childRes, err := childXPath.ExecNode(parent)
		if err != nil || len(childRes) == 0 {
			return "", errors.New("element not found")
		}
		
		// Type assert to get the text node
		if textNode, ok := childRes[0].(tree.Text); ok {
			return string(textNode), nil
		}
		return "", errors.New("not a text node")
	}

	// Extract name
	name, err := extractText(studentNode, "name")
	if err != nil {
		name = ""
	}

	// Extract age (convert to string)
	ageStr, err := extractText(studentNode, "age")
	if err != nil {
		ageStr = ""
	} else {
		// Validate that age is a number
		if _, err := strconv.Atoi(ageStr); err != nil {
			ageStr = ""
		}
	}

	// Extract citizenship
	citizenship, err := extractText(studentNode, "citizenship")
	if err != nil {
		citizenship = ""
	}

	return name, ageStr, citizenship
}