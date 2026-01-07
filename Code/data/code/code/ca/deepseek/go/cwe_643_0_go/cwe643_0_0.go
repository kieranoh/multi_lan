package main

import (
    "errors"
    "strings"

    "github.com/ChrisTrenkamp/goxpath"
    "github.com/ChrisTrenkamp/goxpath/tree"
    "github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // Parse the XML data
    xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
    if err != nil {
        return "", "", ""
    }

    // Build XPath query to find student with matching username and password
    xpathQuery := "/students/student[username='" + username + "' and password='" + password + "']"
    
    // Execute the XPath query
    result, err := goxpath.Exec(xpathQuery, xmlTree, tree.NopFuncs{})
    if err != nil {
        return "", "", ""
    }

    // Check if we found a student
    nodes, ok := result.(tree.NodeSet)
    if !ok || len(nodes) == 0 {
        return "", "", ""
    }

    // Get the first matching student node
    studentNode := nodes[0]

    // Helper function to extract text content from child element
    extractText := func(elementName string) (string, error) {
        xpath := elementName + "/text()"
        res, err := goxpath.Exec(xpath, studentNode, tree.NopFuncs{})
        if err != nil {
            return "", err
        }
        
        if nodeSet, ok := res.(tree.NodeSet); ok && len(nodeSet) > 0 {
            if textNode, ok := nodeSet[0].(tree.Text); ok {
                return string(textNode), nil
            }
        }
        return "", errors.New("element not found")
    }

    // Extract name, age, and citizenship
    name, err := extractText("name")
    if err != nil {
        return "", "", ""
    }

    age, err := extractText("age")
    if err != nil {
        return "", "", ""
    }

    citizenship, err := extractText("citizenship")
    if err != nil {
        return "", "", ""
    }

    return name, age, citizenship
}