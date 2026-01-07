package main

import (
	"errors"
	"fmt"
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
	// XML 데이터가 비어있는 경우 빈 결과 반환
	if strings.TrimSpace(xmlData) == "" {
		return "", "", ""
	}

	// XML 트리 파싱
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// XPath 쿼리 구성: 주어진 username과 password를 가진 student 요소 선택
	xpathExpr := fmt.Sprintf(
		"/students/student[username='%s' and password='%s']",
		escapeXPathString(username),
		escapeXPathString(password),
	)

	// XPath 쿼리 실행
	xpExec := goxpath.MustParse(xpathExpr)
	res, err := xpExec.Exec(xmlTree, tree.NavigatorOptions{})
	if err != nil {
		return "", "", ""
	}

	// 결과가 없는 경우 빈 결과 반환
	if len(res) == 0 {
		return "", "", ""
	}

	// 첫 번째 매칭된 student 요소 가져오기
	studentNode, ok := res[0].(tree.Node)
	if !ok {
		return "", "", ""
	}

	// 이름, 나이, 시민권 정보 추출
	name, err := extractNodeValue(studentNode, "name")
	if err != nil {
		return "", "", ""
	}

	age, err := extractNodeValue(studentNode, "age")
	if err != nil {
		return "", "", ""
	}

	citizenship, err := extractNodeValue(studentNode, "citizenship")
	if err != nil {
		return "", "", ""
	}

	return name, age, citizenship
}

// XPath 문자열에서 특수 문자를 이스케이프합니다.
func escapeXPathString(input string) string {
	// 작은따옴표가 포함된 경우 작은따옴표로 감싸고 내부의 작은따옴표는 이중화
	if strings.Contains(input, "'") {
		// 작은따옴표를 두 개의 작은따옴표로 대체
		escaped := strings.ReplaceAll(input, "'", "''")
		return "'" + escaped + "'"
	}
	// 작은따옴표가 없는 경우 작은따옴표로 감쌈
	return "'" + input + "'"
}

// 주어진 노드에서 자식 요소의 값을 추출합니다.
func extractNodeValue(parent tree.Node, childName string) (string, error) {
	xpathExpr := fmt.Sprintf("%s/text()", childName)
	xpExec := goxpath.MustParse(xpathExpr)
	
	res, err := xpExec.ExecNode(parent, tree.NavigatorOptions{})
	if err != nil {
		return "", err
	}
	
	if len(res) == 0 {
		return "", errors.New("child element not found")
	}
	
	// 결과가 tree.StringVal 타입인지 확인
	strVal, ok := res[0].(tree.StringVal)
	if !ok {
		return "", errors.New("invalid node type")
	}
	
	return string(strVal), nil
}