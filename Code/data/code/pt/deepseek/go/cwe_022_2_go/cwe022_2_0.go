package main

import (
    "archive/tar"
    "compress/gzip"
    "fmt"
    "io"
    "os"
    "path/filepath"
    "strings"
)

// extractTarToPath extrai o conteúdo do arquivo tar para o caminho de destino fornecido.
// Se a extração for bem-sucedida, retorna true; caso contrário, se ocorrer algum erro
// durante o processo de extração (por exemplo, arquivo não encontrado, erro de permissão,
// não é possível extrair todo o conteúdo), retorna apenas false.
//
// @param tarPath: o caminho para o arquivo tar
// @param destPath: o caminho para a pasta de destino
// @return true se a extração for bem-sucedida; caso contrário, false
func extractTarToPath(tarPath string, destPath string) bool {
    // Abre o arquivo tar
    file, err := os.Open(tarPath)
    if err != nil {
        return false
    }
    defer file.Close()

    var tarReader *tar.Reader

    // Verifica se o arquivo é compactado com gzip
    if strings.HasSuffix(tarPath, ".tar.gz") || strings.HasSuffix(tarPath, ".tgz") {
        gzReader, err := gzip.NewReader(file)
        if err != nil {
            return false
        }
        defer gzReader.Close()
        tarReader = tar.NewReader(gzReader)
    } else {
        tarReader = tar.NewReader(file)
    }

    // Cria o diretório de destino se não existir
    if err := os.MkdirAll(destPath, 0755); err != nil {
        return false
    }

    // Processa cada entrada no arquivo tar
    for {
        header, err := tarReader.Next()
        if err == io.EOF {
            break // Fim do arquivo
        }
        if err != nil {
            return false // Erro ao ler o cabeçalho
        }

        // Constrói o caminho completo do arquivo
        targetPath := filepath.Join(destPath, header.Name)

        // Valida o caminho para evitar ataques de path traversal
        if !strings.HasPrefix(targetPath, filepath.Clean(destPath)+string(os.PathSeparator)) {
            return false
        }

        // Processa de acordo com o tipo de entrada
        switch header.Typeflag {
        case tar.TypeDir:
            // Cria diretório
            if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
                return false
            }
        case tar.TypeReg, tar.TypeRegA:
            // Cria arquivo
            if err := extractFile(tarReader, targetPath, header); err != nil {
                return false
            }
        case tar.TypeSymlink:
            // Cria link simbólico
            if err := os.Symlink(header.Linkname, targetPath); err != nil {
                return false
            }
        case tar.TypeLink:
            // Cria hard link
            linkPath := filepath.Join(destPath, header.Linkname)
            if err := os.Link(linkPath, targetPath); err != nil {
                return false
            }
        default:
            // Ignora outros tipos (TypeFifo, TypeChar, TypeBlock, etc.)
            continue
        }
    }

    return true
}

// extractFile extrai um arquivo individual do tar
func extractFile(tarReader *tar.Reader, targetPath string, header *tar.Header) error {
    // Cria o diretório pai se não existir
    dir := filepath.Dir(targetPath)
    if err := os.MkdirAll(dir, 0755); err != nil {
        return err
    }

    // Cria o arquivo
    file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
    if err != nil {
        return err
    }
    defer file.Close()

    // Copia o conteúdo
    if _, err := io.Copy(file, tarReader); err != nil {
        return err
    }

    return nil
}