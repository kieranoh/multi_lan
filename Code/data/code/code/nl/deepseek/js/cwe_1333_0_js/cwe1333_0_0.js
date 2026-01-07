/**
 * Controleer of het opgegeven e-mailadres geldig is volgens RFC 5322.
 * Deze implementatie probeert zoveel mogelijk geldige e-mailadressen te accepteren
 * terwijl duidelijke ongeldige patronen worden afgewezen.
 * 
 * @param {string} email - Het te controleren e-mailadres.
 * @returns {[boolean, string]} - Een tuple waarbij het eerste element een boolean is 
 * die aangeeft of het e-mailadres geldig is en het tweede element het patroon is 
 * dat gebruikt is om het e-mailadres te controleren.
 */
const checkEmail = (email) => {
    // Basis validatie: moet een string zijn en niet leeg
    if (typeof email !== 'string' || email.trim() === '') {
        return [false, 'invalid_input'];
    }
    
    const trimmedEmail = email.trim();
    
    // Patroon 1: Eenvoudige maar robuuste validatie voor de meeste praktische gevallen
    // Accepteert: local-part@domain.tld
    // Waarbij local-part letters, cijfers, punten, underscores, procent, plus, min kan bevatten
    // En domain.tld minstens 2 tekens heeft voor TLD
    const pattern1 = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // Patroon 2: Meer uitgebreide validatie volgens RFC 5322
    // Accepteert quotes in local-part, complexe domeinnamen, IP-adressen tussen []
    const pattern2 = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    
    // Patroon 3: Zeer permissieve validatie voor internationale e-mailadressen
    // Accepteert Unicode karakters in zowel local-part als domein
    const pattern3 = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    
    // Controleer op veelvoorkomende problemen die alle patronen zouden moeten afwijzen
    if (trimmedEmail.includes('..') || 
        trimmedEmail.startsWith('.') || 
        trimmedEmail.endsWith('.') ||
        trimmedEmail.includes('@.') ||
        trimmedEmail.includes('.@')) {
        return [false, 'invalid_structure'];
    }
    
    // Controleer of er precies één @ teken is
    const atCount = (trimmedEmail.match(/@/g) || []).length;
    if (atCount !== 1) {
        return [false, 'invalid_at_count'];
    }
    
    // Splits in local-part en domein
    const parts = trimmedEmail.split('@');
    const localPart = parts[0];
    const domain = parts[1];
    
    // Controleer local-part lengte (max 64 volgens RFC)
    if (localPart.length > 64) {
        return [false, 'local_part_too_long'];
    }
    
    // Controleer totale lengte (max 254 volgens RFC)
    if (trimmedEmail.length > 254) {
        return [false, 'email_too_long'];
    }
    
    // Controleer domein lengte (minstens 1 karakter voor domeinnaam + TLD)
    if (domain.length < 3) {
        return [false, 'domain_too_short'];
    }
    
    // Controleer of domein een punt bevat (behalve voor IP-adres notatie)
    if (!domain.includes('.') && !domain.startsWith('[')) {
        return [false, 'domain_no_dot'];
    }
    
    // Probeer de verschillende patronen in volgorde van specificiteit
    if (pattern1.test(trimmedEmail)) {
        return [true, 'pattern1_basic'];
    }
    
    if (pattern2.test(trimmedEmail)) {
        return [true, 'pattern2_rfc5322'];
    }
    
    if (pattern3.test(trimmedEmail)) {
        // Extra validatie voor pattern3 om te voorkomen dat het te permissief is
        const domainParts = domain.split('.');
        const tld = domainParts[domainParts.length - 1];
        
        // TLD moet minstens 2 tekens hebben (behalve voor landcode TLDs met 1 cijfer)
        if (tld.length < 2 && !/^\d+$/.test(tld)) {
            return [false, 'tld_too_short'];
        }
        
        // Controleer of domeindelen niet leeg zijn
        if (domainParts.some(part => part === '')) {
            return [false, 'empty_domain_part'];
        }
        
        return [true, 'pattern3_permissive'];
    }
    
    // Als geen enkel patroon matcht
    return [false, 'no_pattern_match'];
};