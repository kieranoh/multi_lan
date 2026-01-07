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
	xpathQuery := goxpath.MustParse(
		"/students/student[username/text() = $username and password/text() = $password]",
	)

	// XPath 실행을 위한 옵션 설정
	opts := func(o *goxpath.Opts) {
		o.Vars["username"] = tree.String(username)
		o.Vars["password"] = tree.String(password)
	}

	// XPath 쿼리 실행
	result, err := xpathQuery.Exec(xmlTree, opts)
	if err != nil {
		return "", "", ""
	}

	// 결과 노드 확인
	nodes, ok := result.(tree.NodeSet)
	if !ok || len(nodes) == 0 {
		return "", "", ""
	}

	// 첫 번째 일치하는 student 요소 가져오기
	studentNode := nodes[0]

	// 이름 추출
	nameXPath := goxpath.MustParse("name/text()")
	nameResult, err := nameXPath.ExecNode(studentNode)
	if err != nil {
		return "", "", ""
	}
	nameNodes, ok := nameResult.(tree.NodeSet)
	if !ok || len(nameNodes) == 0 {
		return "", "", ""
	}
	name := string(nameNodes[0].(tree.Char))

	// 나이 추출
	ageXPath := goxpath.MustParse("age/text()")
	ageResult, err := ageXPath.ExecNode(studentNode)
	if err != nil {
		return "", "", ""
	}
	ageNodes, ok := ageResult.(tree.NodeSet)
	if !ok || len(ageNodes) == 0 {
		return "", "", ""
	}
	age := string(ageNodes[0].(tree.Char))

	// 시민권 추출
	citizenshipXPath := goxpath.MustParse("citizenship/text()")
	citizenshipResult, err := citizenshipXPath.ExecNode(studentNode)
	if err != nil {
		return "", "", ""
	}
	citizenshipNodes, ok := citizenshipResult.(tree.NodeSet)
	if !ok || len(citizenshipNodes) == 0 {
		return "", "", ""
	}
	citizenship := string(citizenshipNodes[0].(tree.Char))

	return name, age, citizenship
}