/**
 * Tarkista, onko annettu sähköpostiosoite voimassa. Esimerkiksi, abc.123@def.ghi.com.uk on voimassa oleva sähköpostiosoite.
 * Kattaa mahdollisimman monta tapausta väärien negatiivisten tulosten välttämiseksi.
 *
 * @param {string} email - Tarkistettava sähköposti.
 * @returns {[boolean, string]} - Tupla, jonka ensimmäinen elementti on boolean, joka osoittaa, onko sähköposti voimassa,
 * ja toinen elementti on malli, jota käytettiin sähköpostin tarkistamiseen.
 */
const checkEmail = (email) => {
    // Yleinen sähköpostin regex-malli, joka sallii useimmat yleiset muodot
    const generalPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/;
    
    // Tiukempi malli, joka rajoittaa domain-osan pituutta ja estää peräkkäiset pisteet
    const strictPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/;
    
    // Kattava malli, joka sallii kansainväliset merkit (Unicode) ja pitkät domain-nimet
    const comprehensivePattern = /^[a-zA-Z0-9\u0080-\uFFFF!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9\u0080-\uFFFF!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9\u0080-\uFFFF](?:[a-zA-Z0-9\u0080-\uFFFF-]*[a-zA-Z0-9\u0080-\uFFFF])?\.)+[a-zA-Z\u0080-\uFFFF]{2,}$/;
    
    // Yksinkertainen malli nopeaan perustarkistukseen
    const simplePattern = /^[^@\s]+@[^@\s]+\.[^@\s]+$/;
    
    // Tarkista ensin perussäännöt
    if (typeof email !== 'string' || email.length === 0) {
        return [false, 'invalid_input'];
    }
    
    // Poista ylimääräiset välilyönnit
    const trimmedEmail = email.trim();
    
    // Tarkista perusrakenne: @-merkki ja vähintään yksi piste domain-osassa
    if (!trimmedEmail.includes('@')) {
        return [false, 'no_at_symbol'];
    }
    
    const parts = trimmedEmail.split('@');
    if (parts.length !== 2) {
        return [false, 'multiple_at_symbols'];
    }
    
    const [localPart, domainPart] = parts;
    
    // Tarkista että local-part ja domain-part eivät ole tyhjiä
    if (localPart.length === 0) {
        return [false, 'empty_local_part'];
    }
    
    if (domainPart.length === 0) {
        return [false, 'empty_domain_part'];
    }
    
    // Tarkista että domain-osassa on vähintään yksi piste
    if (!domainPart.includes('.')) {
        return [false, 'no_dot_in_domain'];
    }
    
    // Tarkista että domain-osan viimeinen osa on vähintään 2 merkkiä pitkä
    const domainParts = domainPart.split('.');
    const lastPart = domainParts[domainParts.length - 1];
    if (lastPart.length < 2) {
        return [false, 'tld_too_short'];
    }
    
    // Tarkista ettei sähköposti ala tai lopu pisteellä
    if (trimmedEmail.startsWith('.') || trimmedEmail.endsWith('.')) {
        return [false, 'starts_or_ends_with_dot'];
    }
    
    // Tarkista ettei local-part ala tai lopu pisteellä
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, 'local_part_starts_or_ends_with_dot'];
    }
    
    // Tarkista ettei ole peräkkäisiä pisteitä
    if (trimmedEmail.includes('..')) {
        return [false, 'consecutive_dots'];
    }
    
    // Tarkista pituusrajoitukset (RFC 5321)
    if (trimmedEmail.length > 254) {
        return [false, 'too_long'];
    }
    
    if (localPart.length > 64) {
        return [false, 'local_part_too_long'];
    }
    
    // Yritä ensin tiukkaa mallia
    if (strictPattern.test(trimmedEmail)) {
        return [true, 'strict_pattern'];
    }
    
    // Sitten yleinen malli
    if (generalPattern.test(trimmedEmail)) {
        return [true, 'general_pattern'];
    }
    
    // Sitten kattava malli (kansainväliset merkit)
    if (comprehensivePattern.test(trimmedEmail)) {
        return [true, 'comprehensive_pattern'];
    }
    
    // Lopuksi yksinkertainen malli (viimeinen vaihtoehto)
    if (simplePattern.test(trimmedEmail)) {
        // Tee vielä lisätarkistuksia yksinkertaiselle mallille
        if (domainPart.length <= 253 && 
            !domainPart.startsWith('.') && 
            !domainPart.endsWith('.') &&
            !domainPart.includes('..')) {
            return [true, 'simple_pattern'];
        }
    }
    
    // Jos mikään malli ei täsmää
    return [false, 'no_pattern_match'];
};