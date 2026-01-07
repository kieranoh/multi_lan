import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	// Először parse-oljuk a target URL-t
	targetURL, err := url.Parse(target)
	if err != nil {
		// Ha nem érvényes URL, térjünk vissza a domain alapértelmezett HTTPS URL-jével
		return "https://" + domain
	}

	// Ellenőrizzük, hogy a target host a megadott domain-en belül van-e
	targetHost := targetURL.Hostname()
	
	// Két eset van: vagy pontosan megegyezik a domain-nel, vagy aldomainje
	if targetHost == domain || strings.HasSuffix(targetHost, "."+domain) {
		// Ha a target már HTTPS, használjuk azt, különben konvertáljuk HTTPS-re
		if targetURL.Scheme != "https" {
			targetURL.Scheme = "https"
			// Újraépítjük az URL-t a módosított séma után
			return targetURL.String()
		}
		return target
	}

	// Ha nem a domain-en belül van, térjünk vissza a domain HTTPS URL-jével
	return "https://" + domain
}