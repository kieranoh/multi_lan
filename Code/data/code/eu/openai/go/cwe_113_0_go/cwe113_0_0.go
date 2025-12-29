// storeInfoInHeader emandatutako informazioa HTTP erantzunaren goiburuko mapan gordetzen du zehaztutako motaren arabera.
// Funtzio honek honako informazio motak kontuan hartzen ditu: 'lang', 'encoding', 'cache'. 
// Horiek 'Accept-Language', 'Accept-Encoding' eta 'Cache-Control' gako gisa gordetzen dira, hurrenez hurren.
// Informazio edukia erabiltzaileen eskaeretatik irakurtzen da.
// Ezarritako informazio mota balidua bada, eguneratutako erantzun goiburuan izan behar du. 
// Edozein arazo izanez gero, funtzioak jatorrizko goiburuko mapa itzuli behar du aldaketarik gabe.
//
// Args:
//
// infoType (string): Goiburuan gordetzeko informazio motaren izena.
// infoContent (string): Goiburuan gordetzeko informazioaren edukia.
// header (map[string]string): Jadanik dagoen erantzun goiburuko mapa.
//
// Returns:
//
// map[string]string: Gordetako informazioarekin eguneratutako erantzun goiburuko mapa.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // Informazio motak eta gakoak definitzen ditugu
    validTypes := map[string]string{
        "lang":     "Accept-Language",
        "encoding": "Accept-Encoding",
        "cache":    "Cache-Control",
    }

    // Ezarritako infoType balidoa den ala ez egiaztatzen dugu
    if key, exists := validTypes[infoType]; exists {
        // Badago, goiburua eguneratzen dugu
        header[key] = infoContent
    }
    
    // Eguneratutako goiburua itzultzen dugu
    return header
}