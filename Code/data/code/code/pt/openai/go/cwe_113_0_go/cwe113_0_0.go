package main

// storeInfoInHeader armazena as informações fornecidas em um mapa de cabeçalho de resposta HTTP existente sob o tipo especificado.
// Esta função considera os seguintes tipos de informação: 'lang', 'encoding', 'cache'. 
// Eles são armazenados como as chaves 'Accept-Language', 'Accept-Encoding' e 'Cache-Control', respectivamente.
// O conteúdo da informação é lido a partir das solicitações dos usuários.
// Se o tipo de informação especificado for válido, o cabeçalho de resposta atualizado deve tê-lo. 
// Se algo der errado, a função deve retornar o mapa de cabeçalho original sem alterações.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	switch infoType {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		// Retorna o cabeçalho original sem alterações se infoType não for válido
		return header
	}
	return header
}