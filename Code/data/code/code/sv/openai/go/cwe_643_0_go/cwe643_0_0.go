package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

// Student represents the structure of a student in the XML.
type Student struct {
	Username    string `xml:"username"`
	Password    string `xml:"password"`
	Name        string `xml:"name"`
	Citizenship string `xml:"citizenship"`
	Age         string `xml:"age"`
}

// Students represents the root structure of the XML data.
type Students struct {
	Students []Student `xml:"student"`
}

// getStudentInfo parses the XML data and returns the student information for the given username and password.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	var students Students
	err := xml.Unmarshal([]byte(xmlData), &students)
	if err != nil {
		return "", "", ""
	}

	for _, student := range students.Students {
		if student.Username == username && student.Password == password {
			return student.Name, student.Age, student.Citizenship
		}
	}

	return "", "", ""
}