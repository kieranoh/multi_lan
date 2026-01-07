package main

import (
    "strings"

    "github.com/ChrisTrenkamp/goxpath"
    "github.com/ChrisTrenkamp/goxpath/tree"
    "github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // XML 데이터 파싱
    parsedXML, err := xmltree.ParseXML(strings.NewReader(xmlData))
    if err != nil {
        return "", "", ""
    }

    // XPath 쿼리 구성: 주어진 username과 password를 가진 student 요소 찾기
    xpathExpr := `/students/student[username="` + username + `" and password="` + password + `"]`
    
    // XPath 실행
    xpExec := goxpath.MustParse(xpathExpr)
    results, err := xpExec.Exec(parsedXML, tree.NavigatorOptions{})
    if err != nil {
        return "", "", ""
    }

    // 결과가 없으면 빈 문자열 반환
    if len(results) == 0 {
        return "", "", ""
    }

    // 첫 번째 일치하는 student 요소 가져오기
    studentNode := results[0]

    // 이름 추출
    nameXPath := goxpath.MustParse("name")
    nameResults, err := nameXPath.ExecNode(studentNode.(tree.Node), tree.NavigatorOptions{})
    if err != nil || len(nameResults) == 0 {
        return "", "", ""
    }
    name := nameResults[0].(tree.Elem).ResValue()

    // 나이 추출
    ageXPath := goxpath.MustParse("age")
    ageResults, err := ageXPath.ExecNode(studentNode.(tree.Node), tree.NavigatorOptions{})
    if err != nil || len(ageResults) == 0 {
        return "", "", ""
    }
    age := ageResults[0].(tree.Elem).ResValue()

    // 시민권 추출
    citizenshipXPath := goxpath.MustParse("citizenship")
    citizenshipResults, err := citizenshipXPath.ExecNode(studentNode.(tree.Node), tree.NavigatorOptions{})
    if err != nil || len(citizenshipResults) == 0 {
        return "", "", ""
    }
    citizenship := citizenshipResults[0].(tree.Elem).ResValue()

    return name, age, citizenship
}