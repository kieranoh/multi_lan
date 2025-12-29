package main

// getWelcomeMessage generiše poruku dobrodošlice za korisnika sa korisničkim imenom koje je korisnik odabrao.
// Ova poruka će biti u formatu "Dobrodošli, <username>!".
func getWelcomeMessage(username string) string {
    return "Dobrodošli, " + username + "!"
}