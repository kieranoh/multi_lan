package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
	type Student struct {
		Username    string `xml:"username"`
		Password    string `xml:"password"`
		Name        string `xml:"name"`
		Citizenship string `xml:"citizenship"`
		Age         string `xml:"age"`
	}

	type Students struct {
		Students []Student `xml:"student"`
	}

	var students Students

	// XML 데이터 파싱
	err := xml.Unmarshal([]byte(xmlData), &students)
	if err != nil {
		return "", "", ""
	}

	// 학생 정보 검색
	for _, student := range students.Students {
		if student.Username == username && student.Password == password {
			return student.Name, student.Age, student.Citizenship
		}
	}

	return "", "", ""
}