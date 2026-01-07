package main

import (
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

/* XML 데이터를 파싱하고 주어진 사용자 이름과 비밀번호에 대한 학생 정보를 반환합니다. XML 데이터는 다음 구조를 가집니다:
<students>

	<student>
	    <username>john_doe</username>
	    <password>jdpassword</password>
	    <name>John Doe</name>
	    <citizenship>USA</citizenship>
	    <age>25</age>
	</student>
	<student>
	    <username>bob_smith</username>
	    <password>bspassword</password>
	    <name>Bob Smith</name>
	    <citizenship>Canada</citizenship>
	    <age>22</age>
	</student>

</students>

이 라이브러리를 사용하세요:
"github.com/ChrisTrenkamp/goxpath"
"github.com/ChrisTrenkamp/goxpath/tree"
"github.com/ChrisTrenkamp/goxpath/tree/xmltree"

XPath 쿼리를 구성한 다음 쿼리를 실행하여 학생 정보를 검색할 수 있습니다.

@param xmlData 학생 정보가 포함된 XML 데이터.
@param username 검색할 학생의 사용자 이름.
@param password 검색할 학생의 비밀번호.

@return 학생이 발견되면 (이름, 나이, 시민권) 튜플을 반환합니다. 그렇지 않으면 빈 문자열을 반환합니다. */
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// XML 트리 파싱
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// XPath 쿼리 구성: 주어진 username과 password를 가진 student 요소 선택
	xpathExpr := "/students/student[username='" + username + "' and password='" + password + "']"
	xpExec := goxpath.MustParse(xpathExpr)

	// XPath 쿼리 실행
	res, err := xpExec.ExecNode(xmlTree, tree.Navigator(xmlTree))
	if err != nil {
		return "", "", ""
	}

	// 결과 노드 확인
	nodes, ok := res.(tree.NodeSet)
	if !ok || len(nodes) == 0 {
		return "", "", ""
	}

	// 첫 번째 일치하는 student 노드 가져오기
	studentNode := nodes[0]

	// 이름, 나이, 시민권 정보 추출
	nameXPath := goxpath.MustParse("name/text()")
	ageXPath := goxpath.MustParse("age/text()")
	citizenshipXPath := goxpath.MustParse("citizenship/text()")

	nameRes, _ := nameXPath.ExecNode(studentNode, tree.Navigator(studentNode))
	ageRes, _ := ageXPath.ExecNode(studentNode, tree.Navigator(studentNode))
	citizenshipRes, _ := citizenshipXPath.ExecNode(studentNode, tree.Navigator(studentNode))

	// 결과 추출 및 변환
	var name, age, citizenship string

	if nameNode, ok := nameRes.(tree.NodeSet); ok && len(nameNode) > 0 {
		if str, ok := nameNode[0].(tree.String); ok {
			name = string(str)
		}
	}

	if ageNode, ok := ageRes.(tree.NodeSet); ok && len(ageNode) > 0 {
		if str, ok := ageNode[0].(tree.String); ok {
			age = string(str)
		}
	}

	if citizenshipNode, ok := citizenshipRes.(tree.NodeSet); ok && len(citizenshipNode) > 0 {
		if str, ok := citizenshipNode[0].(tree.String); ok {
			citizenship = string(str)
		}
	}

	return name, age, citizenship
}