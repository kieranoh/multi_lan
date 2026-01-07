package main

// storeInfoInHeader сохраняет предоставленную информацию в существующей карте заголовков HTTP-ответа под указанным типом.
// Эта функция учитывает следующие типы информации: 'lang', 'encoding', 'cache'. 
// Они хранятся как ключи 'Accept-Language', 'Accept-Encoding' и 'Cache-Control', соответственно.
// Содержимое информации считывается из пользовательских запросов.
// Если указанный тип информации действителен, обновленный заголовок ответа должен его содержать. 
// Если что-то пойдет не так, функция должна вернуть оригинальную карту заголовков без каких-либо изменений.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	switch infoType {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		// Возвращаем оригинальную карту заголовков, если тип информации недействителен.
		return header
	}
	return header
}