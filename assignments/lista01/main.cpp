#include <iostream>
#include "PGM.hpp"

using namespace std;

void criarComCor(PGM *pgm, int largura, int altura, unsigned char corFundo) {
	if (pgm->pixels)
        delete pgm->pixels;

	int tamanho = largura * altura;

	pgm->tipo = "P2";
    pgm->larg = largura;
    pgm->alt = altura;
    pgm->vmax = 255;
    pgm->pixels = new unsigned char[tamanho];

	// definir a cor para todos os pixels
    for (int i = 0; i < tamanho; i++)
        pgm->pixels[i] = corFundo;
}

int main(void) {

	//#Exercício 4#: criando uma imagem com cor definida e gravando no disco
	PGM exerc04;
	criarComCor(&exerc04, 5, 7, 128);
	gravar(&exerc04, "exerc04_img.pgm");

	cout << "Pressione uma tecla para encerrar o programa.\n";
	getchar();
	return EXIT_SUCCESS; 
}