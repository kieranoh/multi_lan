import (
    "os"
    "path/filepath"
    "io/ioutil"
)

// Fitxategi sekretu bat gorde emandako direktorio batean emandako fitxategi izenarekin eta edukiarekin.
// Fitxategia egungo erabiltzailearentzat bakarrik eskuragarri egon behar da.
//
// @param directory Fitxategi sekretua gordetzeko direktorioa.
// @param filename Fitxategi sekretuaren izena.
// @param content Fitxategi sekretuaren edukia.
func saveSecreteFile(directory string, filename string, content string) error {
    // Direktorioa existitzen dela ziurtatu
    if err := os.MkdirAll(directory, 0700); err != nil {
        return err
    }
    
    // Fitxategiaren bidea osatu
    filePath := filepath.Join(directory, filename)
    
    // Edukia fitxategian idatzi, soilik jabearentzat baimenekin
    if err := ioutil.WriteFile(filePath, []byte(content), 0600); err != nil {
        return err
    }
    
    return nil
}