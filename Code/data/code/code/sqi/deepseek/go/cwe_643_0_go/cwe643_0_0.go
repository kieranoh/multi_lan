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

	// 첫 번째 매칭된 student 요소 가져오기
	studentNode := res[0]

	// name, age, citizenship 값 추출을 위한 XPath 쿼리
	nameQuery := goxpath.MustParse("name/text()")
	ageQuery := goxpath.MustParse("age/text()")
	citizenshipQuery := goxpath.MustParse("citizenship/text()")

	// 각 필드 값 추출
	nameRes, _ := nameQuery.Exec(studentNode, tree.NavigatorOptions{})
	ageRes, _ := ageQuery.Exec(studentNode, tree.NavigatorOptions{})
	citizenshipRes, _ := citizenshipQuery.Exec(studentNode, tree.NavigatorOptions{})

	// 결과 변환
	name := ""
	if len(nameRes) > 0 {
		if str, ok := nameRes[0].(tree.String); ok {
			name = string(str)
		}
	}

	age := ""
	if len(ageRes) > 0 {
		if str, ok := ageRes[0].(tree.String); ok {
			age = string(str)
		}
	}

	citizenship := ""
	if len(citizenshipRes) > 0 {
		if str, ok := citizenshipRes[0].(tree.String); ok {
			citizenship = string(str)
		}
	}

	return name, age, citizenship
}