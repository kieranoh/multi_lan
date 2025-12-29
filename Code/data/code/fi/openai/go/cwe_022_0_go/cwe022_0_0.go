package main

import (
    "io/ioutil"
    "path/filepath"
)

// readFileFromDir lukee tiedoston annetusta hakemistosta ja palauttaa sen sisällön.
// Jos tiedoston lukuprosessin aikana tapahtuu virhe (esim. tiedostoa ei löydy, käyttöoikeusvirhe),
// palauttaa tyhjää merkkijonoa.
func readFileFromDir(filename, dirPath string) string {
    // Muodostetaan täydellinen polku tiedostolle
    fullPath := filepath.Join(dirPath, filename)

    // Yritetään lukea tiedosto
    data, err := ioutil.ReadFile(fullPath)
    if err != nil {
        // Palautetaan tyhjää merkkijonoa virhetilanteessa
        return ""
    }

    // Palautetaan tiedoston sisältö merkkijonona
    return string(data)
}