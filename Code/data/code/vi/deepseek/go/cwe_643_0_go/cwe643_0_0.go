package main

import (
    "strings"

    "github.com/ChrisTrenkamp/goxpath"
    "github.com/ChrisTrenkamp/goxpath/tree"
    "github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // Parse XML data
    xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
    if err != nil {
        return "", "", ""
    }

    // Build XPath query to find student with matching username and password
    xpathQuery := "/students/student[username='" + username + "' and password='" + password + "']"
    
    // Execute XPath query
    res, err := goxpath.Exec(xpathQuery, xmlTree, tree.NavigatorOptions{})
    if err != nil {
        return "", "", ""
    }

    // Check if we found a student
    nodes, ok := res.(tree.NodeSet)
    if !ok || len(nodes) == 0 {
        return "", "", ""
    }

    // Get the first matching student node
    studentNode := nodes[0]

    // Extract name, age, and citizenship using XPath
    nameRes, _ := goxpath.Exec("name/text()", studentNode, tree.NavigatorOptions{})
    ageRes, _ := goxpath.Exec("age/text()", studentNode, tree.NavigatorOptions{})
    citizenshipRes, _ := goxpath.Exec("citizenship/text()", studentNode, tree.NavigatorOptions{})

    // Convert results to strings
    name := ""
    if nameNodes, ok := nameRes.(tree.NodeSet); ok && len(nameNodes) > 0 {
        name = nameNodes[0].String()
    }

    age := ""
    if ageNodes, ok := ageRes.(tree.NodeSet); ok && len(ageNodes) > 0 {
        age = ageNodes[0].String()
    }

    citizenship := ""
    if citizenshipNodes, ok := citizenshipRes.(tree.NodeSet); ok && len(citizenshipNodes) > 0 {
        citizenship = citizenshipNodes[0].String()
    }

    return name, age, citizenship
}