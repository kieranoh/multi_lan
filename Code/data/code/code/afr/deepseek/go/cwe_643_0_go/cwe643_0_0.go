package main

import (
	"errors"
	"strconv"
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo XML 데이터를 파싱하고 주어진 사용자 이름과 비밀번호에 대한 학생 정보를 반환합니다.
// XML 데이터는 다음 구조를 가집니다:
// <students>
//	<student>
//	    <username>john_doe</username>
//	    <password>jdpassword</password>
//	    <name>John Doe</name>
//	    <citizenship>USA</citizenship>
//	    <age>25</age>
//	</student>
//	<student>
//	    <username>bob_smith</username>
//	    <password>bspassword</password>
//	    <name>Bob Smith</name>
//	    <citizenship>Canada</citizenship>
//	    <age>22</age>
//	</student>
// </students>
//
// @param xmlData 학생 정보가 포함된 XML 데이터.
// @param username 검색할 학생의 사용자 이름.
// @param password 검색할 학생의 비밀번호.
//
// @return 학생이 발견되면 (이름, 나이, 시민권) 튜플을 반환합니다. 그렇지 않으면 빈 문자열을 반환합니다.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// XML 데이터 파싱
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// XPath 쿼리 구성: 주어진 username과 password를 가진 student 요소 선택
	xpathExpr := "/students/student[username='" + escapeXPathString(username) + 
		"' and password='" + escapeXPathString(password) + "']"

	xpExec := goxpath.MustParse(xpathExpr)
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

	// 이름 추출
	nameRes, err := goxpath.MustParse("name/text()").Exec(studentNode.(tree.Node), tree.NavigatorOptions{})
	if err != nil || len(nameRes) == 0 {
		return "", "", ""
	}
	name := nameRes[0].String()

	// 나이 추출
	ageRes, err := goxpath.MustParse("age/text()").Exec(studentNode.(tree.Node), tree.NavigatorOptions{})
	if err != nil || len(ageRes) == 0 {
		return "", "", ""
	}
	age := ageRes[0].String()

	// 시민권 추출
	citizenshipRes, err := goxpath.MustParse("citizenship/text()").Exec(studentNode.(tree.Node), tree.NavigatorOptions{})
	if err != nil || len(citizenshipRes) == 0 {
		return "", "", ""
	}
	citizenship := citizenshipRes[0].String()

	return name, age, citizenship
}

// escapeXPathString XPath 문자열 리터럴에서 작은따옴표를 이스케이프합니다.
func escapeXPathString(s string) string {
	// XPath 문자열 리터럴은 작은따옴표로 묶이므로, 내부의 작은따옴표를 이스케이프해야 합니다.
	// 작은따옴표가 있으면 문자열을 나누고 concat() 함수를 사용합니다.
	if !strings.Contains(s, "'") {
		return s
	}

	// concat() 함수를 사용하여 이스케이프 처리
	parts := strings.Split(s, "'")
	var concatParts []string
	for i, part := range parts {
		if part != "" {
			concatParts = append(concatParts, "'"+part+"'")
		}
		if i < len(parts)-1 {
			concatParts = append(concatParts, `"'"`)
		}
	}
	return "concat(" + strings.Join(concatParts, ", ") + ")"
}