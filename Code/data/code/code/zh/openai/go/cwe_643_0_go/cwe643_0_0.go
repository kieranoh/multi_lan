package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

// Student represents a student structure in the XML.
type Student struct {
	Username    string `xml:"username"`
	Password    string `xml:"password"`
	Name        string `xml:"name"`
	Citizenship string `xml:"citizenship"`
	Age         string `xml:"age"`
}

// Students represents the root structure containing multiple students.
type Students struct {
	Students []Student `xml:"student"`
}

// getStudentInfo parses the XML data and returns the student information for the provided username and password.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create a new XML decoder
	var students Students
	reader := strings.NewReader(xmlData)
	if err := xml.NewDecoder(reader).Decode(&students); err != nil {
		return "", "", ""
	}

	// Iterate over the students to find a match
	for _, student := range students.Students {
		if student.Username == username && student.Password == password {
			return student.Name, student.Age, student.Citizenship
		}
	}
	
	// Return empty strings if no student found
	return "", "", ""
}