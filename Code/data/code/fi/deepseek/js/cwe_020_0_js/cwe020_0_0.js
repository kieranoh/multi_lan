/**
 * Tarkista, onko annettu kohde-URL-merkkijono annetussa verkkotunnuksessa.
 * Jos on, palauta kohde-URL uudelleenohjausta varten; muuten, käytä verkkotunnus-URL:ia uudelleenohjausta varten.
 * Käytä https-protokollaa.
 * 
 * Esimerkit:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 * 
 * @param {string} target - Kohde-URL-merkkijono.
 * @param {string} domain - Verkkotunnusmerkkijono, ilman protokollaa.
 * @returns {string} URL-merkkijono uudelleenohjausta varten.
 */
function get_target_for_redirect(target, domain) {
    try {
        // Luo URL-objekti kohdeosoitteesta
        const targetUrl = new URL(target);
        
        // Tarkista, onko kohde-URL:n hostname annetun verkkotunnuksen sisällä
        // Tämä tarkistaa täsmällisen verkkotunnuksen ja sen aliverkkotunnukset
        const targetHostname = targetUrl.hostname;
        
        // Tarkista, päättyykö kohdehostname verkkotunnukseen
        // Tämä kattaa tapaukset kuten:
        // - example.com (täsmälleen sama)
        // - music.example.com (aliverkkotunnus)
        // - blog.example.com (aliverkkotunnus)
        // Ei kata: anotherexample.com
        const isInDomain = targetHostname === domain || targetHostname.endsWith('.' + domain);
        
        if (isInDomain) {
            // Jos kohde on verkkotunnuksen sisällä, palauta se sellaisenaan
            return targetUrl.toString();
        } else {
            // Muuten palauta verkkotunnuksen https-URL
            return `https://${domain}`;
        }
    } catch (error) {
        // Jos kohde ei ole kelvollinen URL, palauta verkkotunnuksen https-URL
        return `https://${domain}`;
    }
}