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
    xpathExpr := goxpath.MustParse(`/students/student[username="` + username + `" and password="` + password + `"]`)
    
    // XPath 쿼리 실행
    res, err := xpathExpr.ExecNode(xmlTree, tree.NavigatorOptions{})
    if err != nil {
        return "", "", ""
    }

    // 결과가 없으면 빈 문자열 반환
    if len(res) == 0 {
        return "", "", ""
    }

    // 첫 번째 일치하는 student 요소 가져오기
    studentNode := res[0]

    // name, age, citizenship 정보 추출을 위한 XPath 쿼리
    nameXPath := goxpath.MustParse("name")
    ageXPath := goxpath.MustParse("age")
    citizenshipXPath := goxpath.MustParse("citizenship")

    // 각 정보 추출
    nameRes, _ := nameXPath.ExecNode(studentNode, tree.NavigatorOptions{})
    ageRes, _ := ageXPath.ExecNode(studentNode, tree.NavigatorOptions{})
    citizenshipRes, _ := citizenshipXPath.ExecNode(studentNode, tree.NavigatorOptions{})

    // 결과 문자열 추출
    name := ""
    if len(nameRes) > 0 {
        name = tree.String(nameRes[0])
    }

    age := ""
    if len(ageRes) > 0 {
        age = tree.String(ageRes[0])
    }

    citizenship := ""
    if len(citizenshipRes) > 0 {
        citizenship = tree.String(citizenshipRes[0])
    }

    return name, age, citizenship
}