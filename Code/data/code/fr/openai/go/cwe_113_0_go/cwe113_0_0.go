package main

// storeInfoInHeader stocke les informations fournies dans une carte d'en-tête de réponse HTTP existante sous le type spécifié.
// Cette fonction prend en compte les types d'informations suivants : 'lang', 'encoding', 'cache'.
// Ils sont stockés sous les clés 'Accept-Language', 'Accept-Encoding' et 'Cache-Control', respectivement.
// Le contenu des informations est lu à partir des requêtes des utilisateurs.
// Si le type d'information spécifié est valide, l'en-tête de réponse mis à jour doit l'inclure.
// Si quelque chose ne va pas, la fonction doit renvoyer la carte d'en-tête d'origine sans aucune modification.
//
// Args:
// infoType (string): Le type d'information à stocker dans l'en-tête.
// infoContent (string): Le contenu de l'information à stocker dans l'en-tête.
// header (map[string]string): La carte d'en-tête de réponse existante.
//
// Returns:
// map[string]string: La carte d'en-tête de réponse mise à jour avec les informations stockées.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	switch infoType {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		// Retourner la carte d'en-tête d'origine sans modification
		return header
	}
	return header
}