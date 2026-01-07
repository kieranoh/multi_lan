package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

// Student represents the structure for a student in the XML data.
type Student struct {
	Username    string `xml:"username"`
	Password    string `xml:"password"`
	Name        string `xml:"name"`
	Citizenship string `xml:"citizenship"`
	Age         string `xml:"age"`
}

// getStudentInfo parses XML data and returns student information for the given username and password.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create a new XML tree from the provided XML data
	reader := strings.NewReader(xmlData)
	decoder := xml.NewDecoder(reader)
	root, err := xmltree.NewTree(decoder)
	if err != nil {
		return "", "", ""
	}

	// Create an XPath query to find the student with the specified username and password
	query := "//student[username/text()='" + username + "' and password/text()='" + password + "']"
	xp := goxpath.MustCompile(query)

	// Execute the XPath query
	nodes, err := xp.Execute(root)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	// Extract the student data from the found node
	var student Student
	if err := xml.Unmarshal([]byte(nodes[0].String()), &student); err != nil {
		return "", "", ""
	}

	return student.Name, student.Age, student.Citizenship
}