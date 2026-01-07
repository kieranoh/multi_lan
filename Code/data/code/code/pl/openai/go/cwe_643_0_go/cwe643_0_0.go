package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

// getStudentInfo analyzes XML data and returns student information for the given username and password.
// It returns a tuple (name, age, citizenship) if a student is found; otherwise, it returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	xmlData = strings.TrimSpace(xmlData)
	if xmlData == "" {
		return "", "", ""
	}

	// Parse the XML data
	var students struct {
		Students []struct {
			Username    string `xml:"username"`
			Password    string `xml:"password"`
			Name        string `xml:"name"`
			Citizenship string `xml:"citizenship"`
			Age         string `xml:"age"`
		} `xml:"student"`
	}

	err := xml.Unmarshal([]byte(xmlData), &students)
	if err != nil {
		return "", "", ""
	}

	// Iterate over the students and find the matching username and password
	for _, student := range students.Students {
		if student.Username == username && student.Password == password {
			return student.Name, student.Age, student.Citizenship
		}
	}

	return "", "", ""
}