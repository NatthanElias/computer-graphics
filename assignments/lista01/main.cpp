#include <iostream>
#include "PGM.hpp"

using namespace std;

void criarComCor(PGM *pgm, int largura, int altura, unsigned char corFundo);
void setLinha(PGM *pgm, int linha, unsigned char cor);
bool coordValida(PGM *pgm, int x, int y);
void preencherRegiãoQuadrada(PGM *pgm, int x1, int y1, int x2, int y2);

int main(void) {

	setlocale(LC_ALL, "Portuguese");

	//#Exercício 4#: criando uma imagem com cor definida e gravando no disco
	PGM exerc04;
	criarComCor(&exerc04, 200, 200, 128);
	cout << "Exercício 04";
	imprimir(&exerc04);
	gravar(&exerc04, "exerc04_img.pgm");
	destruir(&exerc04);

	//#Exercício 5#: colorindo uma linha da img
	PGM exerc05;
	criarComCor(&exerc05, 20, 20, 128);
	
	setLinha(&exerc05, 10, 255);

	cout << "Exercício 05\n";
	gravar(&exerc05, "exerc05_img.pgm");
	destruir(&exerc05);

	//#Exercício 6#: testando se o pixel é valido
	PGM exerc06;
	criarComCor(&exerc06, 20, 20, 128);
	cout << "Exercício 06\n";
	gravar(&exerc06, "exerc06_img.pgm");

	int x6 = 10;
	int y6 = 22;
	bool testaCord = coordValida(&exerc06, x6, y6);

	if(!testaCord) {
		cout << "As cordenadas (x, y) -> (" << x6 << ", " << y6 << ") não são validas!\n";
	}	else {
		cout << "As cordenadas (x, y) -> (" << x6 << ", " << y6 << ") são validas!\n";
	}
		
	destruir(&exerc06);

	cout << "\nPressione uma tecla para encerrar o programa.\n";
	getchar();
	return EXIT_SUCCESS; 
}

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

void setLinha(PGM *pgm, int linha, unsigned char cor) {

	for(int i = 0; i < pgm->larg; i++) {
		setPixel(pgm, i, linha, cor);
	}
}

bool coordValida(PGM *pgm, int x, int y) {

	if(x < 0 || y < 0 || x >= pgm->larg || y >= pgm->alt)
		return false;

	return true;
}

void preencherRegiãoQuadrada(PGM *pgm, int x1, int y1, int x2, int y2) {
	
	for(int x = x1; x < pgm->larg; x++) {
		
	}
}