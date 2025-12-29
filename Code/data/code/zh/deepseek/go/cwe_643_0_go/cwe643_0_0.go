package main

import (
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// 解析 XML 数据
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// 构建 XPath 查询，查找匹配用户名和密码的学生节点
	xpathExpr := goxpath.MustParse(`/students/student[username="` + username + `" and password="` + password + `"]`)
	
	// 执行 XPath 查询
	result, err := xpathExpr.ExecNode(xmlTree)
	if err != nil {
		return "", "", ""
	}

	// 检查是否找到匹配的学生
	if len(result) == 0 {
		return "", "", ""
	}

	// 获取第一个匹配的学生节点
	studentNode := result[0]

	// 提取学生信息
	nameXPath := goxpath.MustParse("name/text()")
	ageXPath := goxpath.MustParse("age/text()")
	citizenshipXPath := goxpath.MustParse("citizenship/text()")

	nameResult, err := nameXPath.ExecNode(studentNode.(tree.Node))
	if err != nil || len(nameResult) == 0 {
		return "", "", ""
	}

	ageResult, err := ageXPath.ExecNode(studentNode.(tree.Node))
	if err != nil || len(ageResult) == 0 {
		return "", "", ""
	}

	citizenshipResult, err := citizenshipXPath.ExecNode(studentNode.(tree.Node))
	if err != nil || len(citizenshipResult) == 0 {
		return "", "", ""
	}

	// 将结果转换为字符串
	name := tree.String(nameResult[0])
	age := tree.String(ageResult[0])
	citizenship := tree.String(citizenshipResult[0])

	return name, age, citizenship
}