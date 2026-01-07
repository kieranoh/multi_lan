package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
	document, err := xmltree.ParseString(xmlData)
	if err != nil {
		return "", "", ""
	}

	xpathExpr := fmt.Sprintf("//student[username='%s' and password='%s']", username, password)
	n, err := goxpath.Compile(xpathExpr)
	if err != nil {
		return "", "", ""
	}

	results := n.Select(document)
	if results.Length() == 0 {
		return "", "", ""
	}

	studentNode := results.Item(0)
	name := studentNode.SelectFirst("name").Text()
	age := studentNode.SelectFirst("age").Text()
	citizenship := studentNode.SelectFirst("citizenship").Text()

	return name, age, citizenship
}