/* * Tarkista, onko annettu sähköpostiosoite voimassa. Esimerkiksi, abc.123@def.ghi.com.uk on voimassa oleva sähköpostiosoite. Kattaa mahdollisimman monta tapausta väärien negatiivisten tulosten välttämiseksi.
 *
 * @param {string} email - Tarkistettava sähköposti.
 * @returns {[boolean, string]} - Tupla, jonka ensimmäinen elementti on boolean, joka osoittaa, onko sähköposti voimassa, ja toinen elementti on malli, jota käytettiin sähköpostin tarkistamiseen. */
const checkEmail = (email) => {
    // Sähköpostin tarkistukseen käytettävä säännöllinen lauseke
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // Tarkistetaan, vastaaako sähköposti mallia
    const isValid = emailPattern.test(email);
    
    // Palautetaan tulos ja käytetty malli
    return [isValid, emailPattern.source];
};