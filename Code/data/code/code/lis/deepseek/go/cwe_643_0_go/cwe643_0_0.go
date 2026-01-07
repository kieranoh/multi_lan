package main

import (
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// XML 데이터를 파싱하고 주어진 사용자 이름과 비밀번호에 대한 학생 정보를 반환합니다.
// @param xmlData 학생 정보가 포함된 XML 데이터.
// @param username 검색할 학생의 사용자 이름.
// @param password 검색할 학생의 비밀번호.
// @return 학생이 발견되면 (이름, 나이, 시민권) 튜플을 반환합니다. 그렇지 않으면 빈 문자열을 반환합니다.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// XML 데이터 파싱
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// XPath 쿼리 구성: 주어진 username과 password를 가진 student 요소 선택
	xpathExpr := goxpath.MustParse(`/students/student[username="` + username + `" and password="` + password + `"]`)

	// XPath 쿼리 실행
	result, err := xpathExpr.ExecNode(xmlTree)
	if err != nil {
		return "", "", ""
	}

	// 결과가 비어있는지 확인
	if len(result) == 0 {
		return "", "", ""
	}

	// 첫 번째 일치하는 student 요소 가져오기
	studentNode := result[0]

	// 이름, 나이, 시민권 정보 추출을 위한 XPath 쿼리
	nameExpr := goxpath.MustParse("name/text()")
	ageExpr := goxpath.MustParse("age/text()")
	citizenshipExpr := goxpath.MustParse("citizenship/text()")

	// 각 정보 추출
	nameNodes, err := nameExpr.ExecNode(studentNode.(tree.Node))
	if err != nil || len(nameNodes) == 0 {
		return "", "", ""
	}
	name := nameNodes[0].(tree.Elem).ResValue()

	ageNodes, err := ageExpr.ExecNode(studentNode.(tree.Node))
	if err != nil || len(ageNodes) == 0 {
		return "", "", ""
	}
	age := ageNodes[0].(tree.Elem).ResValue()

	citizenshipNodes, err := citizenshipExpr.ExecNode(studentNode.(tree.Node))
	if err != nil || len(citizenshipNodes) == 0 {
		return "", "", ""
	}
	citizenship := citizenshipNodes[0].(tree.Elem).ResValue()

	return name, age, citizenship
}