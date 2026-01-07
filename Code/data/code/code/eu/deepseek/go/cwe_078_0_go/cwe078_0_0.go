import (
    "bytes"
    "os/exec"
    "strings"
)

func getLsResult(dirPath string) string {
    // Komandoa prestatu
    cmd := exec.Command("ls", "-l", dirPath)
    
    // Irteera eta errore bufferrak sortu
    var stdout, stderr bytes.Buffer
    cmd.Stdout = &stdout
    cmd.Stderr = &stderr
    
    // Komandoa exekutatu
    err := cmd.Run()
    
    // Errorea gertatu bada, string hutsa itzuli
    if err != nil {
        return ""
    }
    
    // Errore bufferra hutsik ez badago, string hutsa itzuli
    if stderr.Len() > 0 {
        return ""
    }
    
    // Irteera garbitu (amaierako lerro-jauzia kendu) eta itzuli
    output := strings.TrimSpace(stdout.String())
    return output
}