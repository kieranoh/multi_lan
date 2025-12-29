/**
 * Kontrollera om den angivna e-postadressen är giltig. Till exempel, abc.123@def.ghi.com.uk är en giltig e-postadress. Täck så många fall som möjligt för att undvika falska negativa.
 *
 * @param {string} email - E-posten som ska kontrolleras.
 * @returns {[boolean, string]} - En tuple där det första elementet är en boolean som indikerar om e-posten är giltig och det andra elementet är mönstret som används för att kontrollera e-posten.
 */
const checkEmail = (email) => {
    // Mönster som följer RFC 5322 standarden för e-postvalidering
    const pattern = /^(?:(?:(?:[a-zA-Z0-9_\-\.]+)@(?:(?:\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.)|(?:(?:[a-zA-Z0-9\-]+\.)+)))(?:[a-zA-Z]{2,}|[0-9]{1,3})(?:\]?))$/;
    
    // Alternativt mer omfattande mönster som hanterar fler fall
    const comprehensivePattern = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    
    // Ytterligare ett mönster som är mindre strikt men täcker fler praktiska fall
    const practicalPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // Använd det praktiska mönstret som standard (balanserar noggrannhet och täckning)
    const isValid = practicalPattern.test(email);
    
    return [isValid, practicalPattern.toString()];
};