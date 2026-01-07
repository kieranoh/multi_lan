package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"log"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
	doc, err := xmltree.Parse([]byte(xmlData))
	if err != nil {
		log.Fatalf("Error parsing XML: %v", err)
		return "", "", ""
	}

	xpath := goxpath.NewXPath(doc)
	query := "//student[username='" + username + "' and password='" + password + "']"

	nodes, err := xpath.Query(query)
	if err != nil {
		log.Fatalf("Error querying XML: %v", err)
		return "", "", ""
	}

	if len(nodes) > 0 {
		name := xpath.QueryValue("//student[username='" + username + "' and password='" + password + "']/name")
		age := xpath.QueryValue("//student[username='" + username + "' and password='" + password + "']/age")
		citizenship := xpath.QueryValue("//student[username='" + username + "' and password='" + password + "']/citizenship")
		return name, age, citizenship
	}

	return "", "", ""
}