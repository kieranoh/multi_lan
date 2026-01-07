package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

// getStudentInfo parses XML data and returns student information for the given username and password.
// If the student is found, it returns a tuple of (name, age, citizenship). Otherwise, it returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	var students struct {
		Students []struct {
			Username    string `xml:"username"`
			Password    string `xml:"password"`
			Name        string `xml:"name"`
			Citizenship string `xml:"citizenship"`
			Age         string `xml:"age"`
		} `xml:"student"`
	}

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