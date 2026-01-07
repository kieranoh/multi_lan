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
	xpExec := goxpath.MustParse(xpathQuery)

	// XPath 쿼리 실행
	res, err := xpExec.Exec(xmlTree, tree.NavigatorOptions{})
	if err != nil {
		return "", "", ""
	}

	// 결과가 비어있는지 확인
	if len(res) == 0 {
		return "", "", ""
	}

	// 첫 번째 일치하는 student 요소 가져오기
	studentNode := res[0]

	// student 요소에서 name, age, citizenship 값을 추출하는 XPath 쿼리들
	nameQuery := goxpath.MustParse("name/text()")
	ageQuery := goxpath.MustParse("age/text()")
	citizenshipQuery := goxpath.MustParse("citizenship/text()")

	// 각 정보 추출
	nameRes, err := nameQuery.Exec(studentNode, tree.NavigatorOptions{})
	if err != nil || len(nameRes) == 0 {
		return "", "", ""
	}
	name := nameRes[0].String()

	ageRes, err := ageQuery.Exec(studentNode, tree.NavigatorOptions{})
	if err != nil || len(ageRes) == 0 {
		return "", "", ""
	}
	age := ageRes[0].String()

	citizenshipRes, err := citizenshipQuery.Exec(studentNode, tree.NavigatorOptions{})
	if err != nil || len(citizenshipRes) == 0 {
		return "", "", ""
	}
	citizenship := citizenshipRes[0].String()

	return name, age, citizenship
}