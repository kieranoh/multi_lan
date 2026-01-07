package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

// Student представляет информацию о студенте
type Student struct {
	Username    string `xml:"username"`
	Password    string `xml:"password"`
	Name        string `xml:"name"`
	Citizenship string `xml:"citizenship"`
	Age         string `xml:"age"`
}

// Students представляет корневой элемент с множеством студентов
type Students struct {
	Students []Student `xml:"student"`
}

// getStudentInfo парсит XML-данные и возвращает информацию о студенте для данного имени пользователя и пароля
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