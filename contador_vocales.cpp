#include <iostream>
#include <string>

using namespace std;

// Función para contar las vocales en una cadena
int contarVocales(const string& cadena) {
    string vocales = "aeiouAEIOU";
    int contador = 0;

    for (char caracter : cadena) {
        // Si el carácter es una vocal, incrementar el contador
        if (vocales.find(caracter) == string::npos) {
            contador++;
        }
    }

    return contador;
}

int main() {
    string cadenaUsuario;
    
    cout << "Introduce una cadena de texto: ";
    getline(cin, cadenaUsuario); // Leer toda la línea

    int totalVocales = contarVocales(cadenaUsuario);
    cout << "El número de vocales en la cadena es: " << totalVocales << endl;
    //Comentario de prueba
    return 0;
}
