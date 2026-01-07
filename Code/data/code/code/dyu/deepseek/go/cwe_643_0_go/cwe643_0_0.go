package main

import (
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// XML 데이터 파싱
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// XPath 쿼리 구성
	xpathQuery := goxpath.MustParse(
		"/students/student[username='" + username + "' and password='" + password + "']",
	)

	// XPath 쿼리 실행
	result, err := xpathQuery.ExecNode(xmlTree)
	if err != nil {
		return "", "", ""
	}

	// 결과가 있는지 확인
	if len(result) == 0 {
		return "", "", ""
	}

	// 첫 번째 일치하는 학생 노드 가져오기
	studentNode := result[0]

	// 이름 추출
	nameXPath := goxpath.MustParse("name")
	nameNodes, err := nameXPath.ExecNode(studentNode.(tree.Node))
	if err != nil || len(nameNodes) == 0 {
		return "", "", ""
	}
	name := nameNodes[0].(tree.Elem).ResValue()

	// 나이 추출
	ageXPath := goxpath.MustParse("age")
	ageNodes, err := ageXPath.ExecNode(studentNode.(tree.Node))
	if err != nil || len(ageNodes) == 0 {
		return "", "", ""
	}
	age := ageNodes[0].(tree.Elem).ResValue()

	// 시민권 추출
	citizenshipXPath := goxpath.MustParse("citizenship")
	citizenshipNodes, err := citizenshipXPath.ExecNode(studentNode.(tree.Node))
	if err != nil || len(citizenshipNodes) == 0 {
		return "", "", ""
	}
	citizenship := citizenshipNodes[0].(tree.Elem).ResValue()

	return name, age, citizenship
}