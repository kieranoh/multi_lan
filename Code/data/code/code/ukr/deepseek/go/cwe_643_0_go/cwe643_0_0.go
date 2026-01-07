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

	// XPath 쿼리 구성 - 주어진 사용자 이름과 비밀번호에 해당하는 학생 찾기
	xpathExpr := goxpath.MustParse(
		"/students/student[username='" + username + "' and password='" + password + "']",
	)

	// XPath 쿼리 실행
	res, err := xpathExpr.ExecNode(xmlTree)
	if err != nil {
		return "", "", ""
	}

	// 결과가 없으면 빈 문자열 반환
	if len(res) == 0 {
		return "", "", ""
	}

	// 첫 번째 매칭된 학생 노드 가져오기
	studentNode := res[0]

	// 이름 추출
	nameXPath := goxpath.MustParse("name")
	nameRes, err := nameXPath.ExecNode(studentNode.(tree.Node))
	if err != nil || len(nameRes) == 0 {
		return "", "", ""
	}
	name := nameRes[0].(tree.Elem).ResValue()

	// 나이 추출
	ageXPath := goxpath.MustParse("age")
	ageRes, err := ageXPath.ExecNode(studentNode.(tree.Node))
	if err != nil || len(ageRes) == 0 {
		return "", "", ""
	}
	age := ageRes[0].(tree.Elem).ResValue()

	// 시민권 추출
	citizenshipXPath := goxpath.MustParse("citizenship")
	citizenshipRes, err := citizenshipXPath.ExecNode(studentNode.(tree.Node))
	if err != nil || len(citizenshipRes) == 0 {
		return "", "", ""
	}
	citizenship := citizenshipRes[0].(tree.Elem).ResValue()

	return name, age, citizenship
}