package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

// Student represents the structure of a student in the XML data.
type Student struct {
	Username    string `xml:"username"`
	Password    string `xml:"password"`
	Name        string `xml:"name"`
	Citizenship string `xml:"citizenship"`
	Age         string `xml:"age"`
}

/*
XML 데이터를 파싱하고 주어진 사용자 이름과 비밀번호에 대한 학생 정보를 반환합니다. XML 데이터는 다음 구조를 가집니다:
<students>
	<student>
	    <username>john_doe</username>
	    <password>jdpassword</password>
	    <name>John Doe</name>
	    <citizenship>USA</citizenship>
	    <age>25</age>
	</student>
	<student>
	    <username>bob_smith</username>
	    <password>bspassword</password>
	    <name>Bob Smith</name>
	    <citizenship>Canada</citizenship>
	    <age>22</age>
	</student>
</students>

@param xmlData 학생 정보가 포함된 XML 데이터.
@param username 검색할 학생의 사용자 이름.
@param password 검색할 학생의 비밀번호.

@return 학생이 발견되면 (이름, 나이, 시민권) 튜플을 반환합니다. 그렇지 않으면 빈 문자열을 반환합니다.
*/
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Create a new XML tree from the provided XML data
	tree, err := xmltree.Parse(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Create a new XPath selector
	xpath := goxpath.New(tree)

	// XPath query to find the student with the given username and password
	query := "//student[username='" + username + "' and password='" + password + "']"

	// Execute the XPath query
	nodes, err := xpath.Query(query)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	// Extract student information
	var student Student
	for _, node := range nodes {
		if err := xml.Unmarshal([]byte(node.String()), &student); err == nil {
			return student.Name, student.Age, student.Citizenship
		}
	}

	return "", "", ""
}