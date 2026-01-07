package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

// Student struct to hold student information
type Student struct {
	Username    string `xml:"username"`
	Password    string `xml:"password"`
	Name        string `xml:"name"`
	Citizenship string `xml:"citizenship"`
	Age         string `xml:"age"`
}

// Students struct to hold a list of students
type Students struct {
	Students []Student `xml:"student"`
}

// getStudentInfo parses the XML data and returns student information for the given username and password.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	var students Students
	decoder := xml.NewDecoder(strings.NewReader(xmlData))
	if err := decoder.Decode(&students); err != nil {
		return "", "", ""
	}

	for _, student := range students.Students {
		if student.Username == username && student.Password == password {
			return student.Name, student.Age, student.Citizenship
		}
	}
	return "", "", ""
}