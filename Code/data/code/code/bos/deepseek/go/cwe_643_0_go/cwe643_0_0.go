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
	res, err := xpExec.Exec(xmlTree, func(o *goxpath.Opts) {
		o.NS = make(map[string]string)
	})
	if err != nil {
		return "", "", ""
	}

	// 결과가 비어있는지 확인
	if res.(tree.NodeSet).Size() == 0 {
		return "", "", ""
	}

	// 첫 번째 매칭된 student 요소 가져오기
	studentNode := res.(tree.NodeSet)[0]

	// name, age, citizenship 값 추출을 위한 XPath 쿼리들
	nameXPath := goxpath.MustParse("name/text()")
	ageXPath := goxpath.MustParse("age/text()")
	citizenshipXPath := goxpath.MustParse("citizenship/text()")

	// 각 정보 추출
	nameRes, _ := nameXPath.Exec(studentNode, func(o *goxpath.Opts) {
		o.NS = make(map[string]string)
	})
	ageRes, _ := ageXPath.Exec(studentNode, func(o *goxpath.Opts) {
		o.NS = make(map[string]string)
	})
	citizenshipRes, _ := citizenshipXPath.Exec(studentNode, func(o *goxpath.Opts) {
		o.NS = make(map[string]string)
	})

	// 결과를 문자열로 변환
	name := ""
	if nameRes != nil && nameRes.(tree.NodeSet).Size() > 0 {
		name = string(nameRes.(tree.NodeSet)[0].(tree.Char).String())
	}

	age := ""
	if ageRes != nil && ageRes.(tree.NodeSet).Size() > 0 {
		age = string(ageRes.(tree.NodeSet)[0].(tree.Char).String())
	}

	citizenship := ""
	if citizenshipRes != nil && citizenshipRes.(tree.NodeSet).Size() > 0 {
		citizenship = string(citizenshipRes.(tree.NodeSet)[0].(tree.Char).String())
	}

	return name, age, citizenship
}