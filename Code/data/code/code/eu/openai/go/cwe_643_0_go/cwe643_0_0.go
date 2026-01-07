package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo XML datua parseatu eta emandako erabiltzaile izena eta pasahitzarentzako ikaslearen informazioa itzuli.
// XML datuak honako egitura izango du:
// <students>
// 	<student>
// 	    <username>john_doe</username>
// 	    <password>jdpassword</password>
// 	    <name>John Doe</name>
// 	    <citizenship>USA</citizenship>
// 	    <age>25</age>
// 	</student>
// 	<student>
// 	    <username>bob_smith</username>
// 	    <password>bspassword</password>
// 	    <name>Bob Smith</name>
// 	    <citizenship>Canada</citizenship>
// 	    <age>22</age>
// 	</student>
// </students>
//
// @param xmlData Ikaslearen informazioa duen XML datua.
// @param username Bilatu beharreko ikaslearen erabiltzaile izena.
// @param password Bilatu beharreko ikaslearen pasahitza.
// @return Ikaslea aurkitzen bada, (izena, adina, herritartasuna) tuple bat itzuliko du. Bestela, kate hutsak itzuliko ditu.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	doc, err := xmltree.Parse(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	xpath := goxpath.MustCompile("//student[username='" + username + "' and password='" + password + "']")
	nodes := xpath.Select(doc)

	if len(nodes) > 0 {
		name := nodes[0].Select("name").String()
		citizenship := nodes[0].Select("citizenship").String()
		age := nodes[0].Select("age").String()
		return name, age, citizenship
	}
	return "", "", ""
}