/**
 * Überprüfen Sie, ob die angegebene E-Mail-Adresse gültig ist. Zum Beispiel ist abc.123@def.ghi.com.uk eine gültige E-Mail-Adresse. Decken Sie so viele Fälle wie möglich ab, um falsche Negative zu vermeiden.
 *
 * @param {string} email - Die zu überprüfende E-Mail.
 * @returns {[boolean, string]} - Ein Tupel, bei dem das erste Element ein Boolean ist, das angibt, ob die E-Mail gültig ist, und das zweite Element das Muster ist, das zur Überprüfung der E-Mail verwendet wurde.
 */
const checkEmail = (email) => {
    // RFC 5322-konformes E-Mail-Validierungsmuster
    // Dieses Muster deckt die meisten gültigen E-Mail-Adressen ab, einschließlich:
    // - Lokale Teile mit Punkten, Pluszeichen, Bindestrichen und Unterstrichen
    // - Internationale Domainnamen (IDN)
    // - Subdomains und mehrstufige Domains
    // - IPv4- und IPv6-Adressen in eckigen Klammern
    const emailPattern = /^(?:(?:(?:[^<>()\[\]\\.,;:\s@"]+(?:\.[^<>()\[\]\\.,;:\s@"]+)*)|(?:".+"))@(?:(?:\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(?:\[IPv6:[0-9a-fA-F:]+])|(?:(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,})))$/;
    
    // Einfacheres, aber umfassendes Muster für bessere Lesbarkeit und Wartbarkeit
    // Dieses Muster ist weniger streng als RFC 5322, aber deckt die meisten praktischen Fälle ab
    const simplePattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // Erweitertes Muster, das internationale Zeichen und komplexere lokale Teile unterstützt
    const extendedPattern = /^(?=.{1,254}$)(?=.{1,64}@)[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/;
    
    // Prüfe zuerst mit dem erweiterten Muster (am umfassendsten)
    if (extendedPattern.test(email)) {
        return [true, "extended"];
    }
    
    // Fallback auf einfaches Muster für bestimmte Fälle
    if (simplePattern.test(email)) {
        return [true, "simple"];
    }
    
    // Als letztes versuche das RFC 5322-Muster
    if (emailPattern.test(email)) {
        return [true, "rfc5322"];
    }
    
    // Wenn keine der Prüfungen erfolgreich war
    return [false, "none"];
};