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
    const domainWithProtocol = `https://${domain}`;
    
    // Tarkista, sisältääkö kohde-URL annettavan verkkotunnuksen
    if (target.startsWith(domainWithProtocol) || target.startsWith(`https://${domain}`) || 
        target.includes(`.${domain}`)) {
        return target;
    }
    
    return domainWithProtocol;
}