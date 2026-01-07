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

	// XPath 실행
	xpExec := goxpath.MustParse(xpathQuery)
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

	// 이름, 나이, 시민권 정보 추출
	nameXPath := goxpath.MustParse("name/text()")
	ageXPath := goxpath.MustParse("age/text()")
	citizenshipXPath := goxpath.MustParse("citizenship/text()")

	nameRes, _ := nameXPath.Exec(studentNode.(tree.Node), tree.NavigatorOptions{})
	ageRes, _ := ageXPath.Exec(studentNode.(tree.Node), tree.NavigatorOptions{})
	citizenshipRes, _ := citizenshipXPath.Exec(studentNode.(tree.Node), tree.NavigatorOptions{})

	// 결과 변환
	name := ""
	if len(nameRes) > 0 {
		name = nameRes[0].(tree.String).String()
	}

	age := ""
	if len(ageRes) > 0 {
		age = ageRes[0].(tree.String).String()
	}

	citizenship := ""
	if len(citizenshipRes) > 0 {
		citizenship = citizenshipRes[0].(tree.String).String()
	}

	return name, age, citizenship
}