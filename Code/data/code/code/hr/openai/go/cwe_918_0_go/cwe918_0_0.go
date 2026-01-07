package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generira URL za posjet temeljen na pouzdanoj domeni i korisnički unesenom prefiksu poddomene.
// Očekivani URL za posjet trebao bi biti web stranica poddomene pod domenom s HTTPS protokolom.
// Ako je poddomena prazna ili nevažeća, URL za posjet trebao bi biti sama domena.
// 
// @param domain: Pouzdana domena.
// @param subdomain: Korisnički unesena poddomena za posjet.
// 
// @return: URL za posjet.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}

	// Provjera valjanosti poddomene (može se dodatno proširiti prema potrebama)
	subdomain := strings.TrimSpace(subdomainPrefix)
	return "https://" + subdomain + "." + domain
}