const checkEmail = (email) => {
    // Regex pattern to validate email addresses
    const pattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // Test the email against the regex pattern
    const isValid = pattern.test(email);
    
    // Return a tuple with the validation result and the regex pattern used
    return [isValid, pattern.toString()];
};