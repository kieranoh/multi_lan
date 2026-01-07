package main

import (
	"database/sql"
)

func getUser(db *sql.DB, username, password string) string {
	// SQL क्वेरी तैयार करें
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	// क्वेरी निष्पादित करें
	var userInfo string
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	// त्रुटि जाँचें
	if err != nil {
		if err == sql.ErrNoRows {
			// कोई उपयोगकर्ता नहीं मिला
			return ""
		}
		// अन्य डेटाबेस त्रुटि
		return ""
	}
	
	// उपयोगकर्ता जानकारी लौटाएं
	return userInfo
}