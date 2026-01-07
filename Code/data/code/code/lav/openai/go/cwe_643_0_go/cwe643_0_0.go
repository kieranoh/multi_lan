package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo parses the XML data and returns the student information for the given username and password.
// XML data structure is as follows:
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
// @param xmlData XML data containing student information.
// @param username The username of the student to search for.
// @param password The password of the student to search for.
// 
// @return A tuple (name, age, citizenship) if the student is found, otherwise returns empty strings.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	reader := xmltree.NewReader([]byte(xmlData))
	document, err := xmltree.Parse(reader)
	if err != nil {
		return "", "", ""
	}

	xpathExpr := fmt.Sprintf("//student[username='%s' and password='%s']", username, password)
	res, err := goxpath.Query(document, xpathExpr)
	if err != nil || len(res) == 0 {
		return "", "", ""
	}

	name := res[0].Select("name").Text()
	age := res[0].Select("age").Text()
	citizenship := res[0].Select("citizenship").Text()

	return name, age, citizenship
}