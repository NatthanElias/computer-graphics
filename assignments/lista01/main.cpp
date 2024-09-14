#include <iostream>
#include "PGM.hpp"

using namespace std;

void criarComCor(PGM *pgm, int largura, int altura, unsigned char corFundo);
void setLinha(PGM *pgm, int linha, unsigned char cor);
bool coordValida(PGM *pgm, int x, int y);
string preencherRegiãoQuadrada(PGM *pgm, int x1, int y1, int x2, int y2, string cor);

int main(void) {

	setlocale(LC_ALL, "pt_BR.UTF-8");

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
	int y6 = 11;
	bool testaCord = coordValida(&exerc06, x6, y6);

	if(!testaCord) {
		cout << "As cordenadas (x, y) -> (" << x6 << ", " << y6 << ") não são validas!\n";
	}	else {
		cout << "As cordenadas (x, y) -> (" << x6 << ", " << y6 << ") são validas!\n";
	}

	destruir(&exerc06);

	//#Exercício 7#: pintar regiao quadrada
	PGM exerc07;
	criarComCor(&exerc07, 200, 200, 64);
	cout << "Exercício 07\n";
	
	string cor = "branco";
	preencherRegiãoQuadrada(&exerc07, 50, 50, 100, 100, cor);
	gravar(&exerc07, "exerc07_img.pgm");
		
	destruir(&exerc07);

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

string preencherRegiãoQuadrada(PGM *pgm, int x1, int y1, int x2, int y2, string cor) {

	unsigned char corValue = 0;

	if(cor == "branco") {
		corValue = 255;
	} else if(cor == "preto") {
		corValue = 0;
	} else if(cor == "cinza") {
		corValue = 128;
	} else {
		return "Especifique uma cor válida!";
	}
	
	// Garantir que x1 seja menor ou igual a x2 e y1 seja menor ou igual a y2
    int inicioX = std::min(x1, x2);
    int fimX = std::max(x1, x2);
    int inicioY = std::min(y1, y2);
    int fimY = std::max(y1, y2);

    // Verificar se todas as coordenadas estão dentro dos limites antes do loop
    if (!coordValida(pgm, inicioX, inicioY) || !coordValida(pgm, fimX, fimY)) {
        return "Coordenadas fora dos limites!";
    }

    // Percorrer os pixels na área especificada
    for (int i = inicioX; i <= fimX; i++) {
        for (int j = inicioY; j <= fimY; j++) {
            // Garantir que as coordenadas sejam válidas antes de definir o pixel
            if (coordValida(pgm, i, j)) {
                setPixel(pgm, i, j, corValue);
            }
        }
    }

    return "Região preenchida com sucesso!";
}