/**
 * Controleer of het opgegeven e-mailadres geldig is. Bijvoorbeeld, abc.123@def.ghi.com.uk is een geldig e-mailadres. Dek zoveel mogelijk gevallen af om valse negatieven te voorkomen.
 *
 * @param {string} email - Het te controleren e-mailadres.
 * @returns {[boolean, string]} - Een tuple waarbij het eerste element een boolean is die aangeeft of het e-mailadres geldig is en het tweede element het patroon is dat gebruikt is om het e-mailadres te controleren.
 */
const checkEmail = (email) => {
    // Regex patroon voor het valideren van een e-mailadres
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    const isValid = emailPattern.test(email);
    return [isValid, emailPattern.toString()];
};