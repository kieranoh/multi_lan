function search_pattern(pattern, content) {
    // Перевіряємо, чи задані параметри є рядками
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }

    // Використовуємо регулярний вираз для пошуку патерну в контенті
    const regex = new RegExp(pattern);
    return regex.test(content);
}