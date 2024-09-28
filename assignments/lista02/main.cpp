#include <iostream>
#include "PPM.hpp"

using namespace std;

void criarComCor(PPM *ppm, int largura, int altura, RGB corFundo);
void setLinha(PPM *ppm, int linha, RGB cor);
bool coordValida(PPM *ppm, int x, int y);
void marcarArea(PPM *ppm, int x1, int y1, int x2, int y2, RGB cor);

int main(void)
{
	//#Exercício3#: criar imagem com cor RGB
	PPM exerc3;
	RGB corRGB(255,0,0);
	cout << "\n\n#Exercício 3#\n";
	criarComCor(&exerc3, 200, 200, corRGB);
	gravar(&exerc3, "exerc3_rgb.ppm");
	cout << "Imagem foi gravada!\n";
	destruir(&exerc3);

	//#Exercício4#: pintar linha com cor RGB
	PPM exerc4;
	RGB corRGBcria(255,0,0); 
	RGB corRGBlinha(0,255,255); 
	cout << "\n\n#Exercício 4#\n";
	criarComCor(&exerc4, 21, 21, corRGB);
	setLinha(&exerc4, 11, corRGBlinha);
	gravar(&exerc4, "exerc4_rgb.ppm");
	cout << "Imagem foi gravada!\n";
	destruir(&exerc4);

	//#Exercício6#: marcar uma area com cor RGB
	PPM exerc6;
	RGB corRGBcria2(255,0,0); 
	RGB corRGBarea(0,255,255); 
	cout << "\n\n#Exercício 6#\n";
	criarComCor(&exerc6, 150, 200, corRGB);
	marcarArea(&exerc6, 67, 30, 100, 300, corRGBarea);
	gravar(&exerc6, "exerc6_rgb.ppm");
	cout << "Imagem foi gravada!\n";
	destruir(&exerc6);


	cout << "Pressione uma tecla para encerrar o programa.\n";
	getchar();
	return EXIT_SUCCESS; 
}

void criarComCor(PPM *ppm, int largura, int altura, RGB corFundo) {
	
	if (ppm->pixels)
        delete ppm->pixels;

	int tamanho = largura * altura * 3;

	ppm->tipo = "P3";
    ppm->larg = largura;
    ppm->alt = altura;
    ppm->vmax = 255;
    ppm->pixels = new unsigned char[tamanho];

	// definir a cor para todos os pixels
    for (int i = 0; i < tamanho ; i+=3) {
		ppm->pixels[i] = corFundo.r;
		ppm->pixels[i+1] = corFundo.g;
		ppm->pixels[i+2] = corFundo.b;
	}
}

void setLinha(PPM *ppm, int linha, RGB cor) {
	
	for(int i=0; i < ppm->larg; i++) 
		setPixel(ppm, i, linha, cor);
}

bool coordValida(PPM *ppm, int x, int y) {
	
	if(x < 0 || y < 0 || x >= ppm->larg || y >= ppm->alt)
		return false;
	
	return true;
}

void marcarArea(PPM *ppm, int x1, int y1, int x2, int y2, RGB cor) {
	
	// garante que x1 nao sera negativo
	x1 = min(x1,x2);
	x1 = max(x1, 0);

	//garante que o x2 nao sera maior que a largura
	x2 = max(x1,x2);
	x2 = min(x2, ppm->larg-1);

	// pintar linha
	for (int i = x1; i <= x2 ; i++) {
		setPixel(ppm, i, y1, cor);
		setPixel(ppm, i, y2, cor);
	}

	y1 = min(y1,y2);
	y1 = max(y1,0);
	cout << "Y1:" << y1 << endl;

	y2 = max(y1,y2);
	y2 = min(y2, ppm->alt+1);

	//pintar coluna
	for (int j = y1; j <= y2 ; j++) {
		setPixel(ppm, x1, j, cor);
		setPixel(ppm, x2, j, cor);
	}
}