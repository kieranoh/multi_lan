package main

import (
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// XML fa felépítése
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// XPath lekérdezés összeállítása a megadott felhasználónév és jelszó alapján
	xpathExpr := "/students/student[username='" + username + "' and password='" + password + "']"
	
	// XPath lekérdezés végrehajtása
	xpExec := goxpath.MustParse(xpathExpr)
	res, err := xpExec.Exec(tree.Node(xmlTree))
	if err != nil {
		return "", "", ""
	}

	// Ellenőrizzük, hogy találtunk-e diákot
	nodes := res.(tree.NodeSet)
	if len(nodes) == 0 {
		return "", "", ""
	}

	// Az első egyező diák elemeinek kinyerése
	studentNode := nodes[0]

	// Név kinyerése
	nameXPath := goxpath.MustParse("name")
	nameRes, err := nameXPath.Exec(tree.Node(studentNode))
	if err != nil {
		return "", "", ""
	}
	name := ""
	if nameNodes, ok := nameRes.(tree.NodeSet); ok && len(nameNodes) > 0 {
		name = string(nameNodes[0].(tree.Char))
	}

	// Kor kinyerése
	ageXPath := goxpath.MustParse("age")
	ageRes, err := ageXPath.Exec(tree.Node(studentNode))
	if err != nil {
		return "", "", ""
	}
	age := ""
	if ageNodes, ok := ageRes.(tree.NodeSet); ok && len(ageNodes) > 0 {
		age = string(ageNodes[0].(tree.Char))
	}

	// Állampolgárság kinyerése
	citizenshipXPath := goxpath.MustParse("citizenship")
	citizenshipRes, err := citizenshipXPath.Exec(tree.Node(studentNode))
	if err != nil {
		return "", "", ""
	}
	citizenship := ""
	if citizenshipNodes, ok := citizenshipRes.(tree.NodeSet); ok && len(citizenshipNodes) > 0 {
		citizenship = string(citizenshipNodes[0].(tree.Char))
	}

	return name, age, citizenship
}