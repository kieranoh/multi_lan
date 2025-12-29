import (
    "io"
    "os"
    "path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
    // Egiaztatu parametroak hutsik ez daudela
    if filename == "" || dirPath == "" {
        return ""
    }
    
    // Osatu fitxategiaren bide osoa
    filePath := filepath.Join(dirPath, filename)
    
    // Egiaztatu fitxategia existitzen dela
    fileInfo, err := os.Stat(filePath)
    if err != nil {
        return ""
    }
    
    // Egiaztatu fitxategia arrunta dela eta ez direktorioa
    if fileInfo.IsDir() {
        return ""
    }
    
    // Ireki fitxategia irakurtzeko
    file, err := os.Open(filePath)
    if err != nil {
        return ""
    }
    defer file.Close()
    
    // Irakurri fitxategiaren edukia
    content, err := io.ReadAll(file)
    if err != nil {
        return ""
    }
    
    return string(content)
}