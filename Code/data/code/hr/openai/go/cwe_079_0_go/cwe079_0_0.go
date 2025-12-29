package main

// getWelcomeMessage generira poruku dobrodošlice za korisnika s korisničkim imenom koje je korisnik odredio.
// Ova poruka će se prikazati na HTML stranici nakon što se korisnik prijavi.
// Poruka će biti u formatu "Dobrodošli, <username>!".
func getWelcomeMessage(username string) string {
    return "Dobrodošli, " + username + "!"
}