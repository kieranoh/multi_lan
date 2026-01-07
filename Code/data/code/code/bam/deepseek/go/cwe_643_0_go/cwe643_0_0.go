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

	// XPath 쿼리 구성: 주어진 username과 password를 가진 student 요소 선택
	xpathQuery := "/students/student[username='" + username + "' and password='" + password + "']"

	// XPath 쿼리 실행
	xpExec := goxpath.MustParse(xpathQuery)
	res, err := xpExec.Exec(tree.Node(xmlTree))
	if err != nil {
		return "", "", ""
	}

	// 결과 노드 목록 확인
	nodes := res.(tree.NodeSet)
	if len(nodes) == 0 {
		return "", "", ""
	}

	// 첫 번째 일치하는 student 노드 가져오기
	studentNode := nodes[0]

	// 이름 추출
	nameXPath := goxpath.MustParse("name")
	nameRes, err := nameXPath.Exec(tree.Node(studentNode))
	if err != nil {
		return "", "", ""
	}
	nameNodes := nameRes.(tree.NodeSet)
	if len(nameNodes) == 0 {
		return "", "", ""
	}
	name := nameNodes[0].ResValue()

	// 나이 추출
	ageXPath := goxpath.MustParse("age")
	ageRes, err := ageXPath.Exec(tree.Node(studentNode))
	if err != nil {
		return "", "", ""
	}
	ageNodes := ageRes.(tree.NodeSet)
	if len(ageNodes) == 0 {
		return "", "", ""
	}
	age := ageNodes[0].ResValue()

	// 시민권 추출
	citizenshipXPath := goxpath.MustParse("citizenship")
	citizenshipRes, err := citizenshipXPath.Exec(tree.Node(studentNode))
	if err != nil {
		return "", "", ""
	}
	citizenshipNodes := citizenshipRes.(tree.NodeSet)
	if len(citizenshipNodes) == 0 {
		return "", "", ""
	}
	citizenship := citizenshipNodes[0].ResValue()

	return name, age, citizenship
}