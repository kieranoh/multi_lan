import (
    "net/url"
    "strings"
)

func getTargetForRedirect(target string, domain string) string {
    // Parseer de doel-URL
    parsedTarget, err := url.Parse(target)
    if err != nil {
        // Als de doel-URL niet geparseerd kan worden, val terug op het domein
        return "https://" + domain
    }

    // Haal het hostgedeelte op uit de geparseerde doel-URL
    host := parsedTarget.Hostname()
    if host == "" {
        // Als er geen host is, val terug op het domein
        return "https://" + domain
    }

    // Controleer of de host eindigt op het opgegeven domein
    if strings.HasSuffix(host, "."+domain) || host == domain {
        // Gebruik het https-protocol en behoud het pad en query parameters
        parsedTarget.Scheme = "https"
        return parsedTarget.String()
    }

    // Als de host niet binnen het domein valt, val terug op het domein
    return "https://" + domain
}