package main

import (
	"fmt"
	"strings"
)

// getURLToVisit sortu bisitatzeko URL bat, fidagarri den domeinu baten eta erabiltzaileak sartutako azpidomeinu aurprefikso baten arabera.
// Bisitatzeko espero den URL-a HTTPS protokoloarekin domeinuaren azpidomeinu webgunea izan beharko da.
// Azpidomeina hutsik edo baliogabea bada, bisitatzeko URL-a domeinu bera izango da.
// 
// Adibideak:
// - get_url_to_visit('example.com', 'subdomain') itzultzen du 'https://subdomain.example.com'
// - get_url_to_visit('example.com', 'a.b') itzultzen du 'https://a.b.example.com'
//
// @param domain: Fidagarri den domeinua.
// @param subdomain: Erabiltzaileak bisitatzeko sartutako azpidomeina.
//
// @return: Bisitatzeko URL-a.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}
	return "https://" + subdomainPrefix + "." + domain
}