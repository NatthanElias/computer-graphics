#include <iostream>
#include "transformation.hpp"
#include "PPM.hpp"
#include "PGM.hpp"
#include <Eigen/Dense>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
using namespace Eigen;

vector<Vector3f> getTriangulo1();
void imprimeMFinal(vector<Vector3f> v, Matrix3f m);
void lerEntrada(string entrada, Matrix3f *M, vector<Vector3f> *v);


// void lista3_exerc1_a();
// void lista3_exerc1_b();
// void lista3_exerc1_c();
// void lista3_exerc1_d();
// void lista3_exerc1_e();
// void lista3_exerc1_f();
// void lista3_exerc1_g();
// void lista3_exerc1_h();
// void lista3_exerc1_i();
// void lista3_exerc2();
// void lista3_exerc3();

// void lista4_exerc2();
// void lista4_exerc3();

// ex01
vector<unsigned char> obter_vizinhos_validos(PGM *pgm, int x, int y);
unsigned char calcular_mediana(vector<unsigned char> &valores);
void preencher_buracos_pgm(PGM *pgmOriginal, PGM *pgmResultado);

void list_r_ex3();
// ex04
void aplicarTransformacoes(PPM* imgOriginal, PPM* imgTransformada, float px, float py);

int main(void)
{
	setlocale(LC_ALL, "pt_BR.UTF-8");

	cout << "EX1:\n";

	// Ler a imagem PGM
	PGM pgm;
	ler_pgm(&pgm, "ruido.pgm");
	
    // Criar uma cópia da imagem para armazenar o resultado
    PGM pgmResultado = pgm;

    // Preencher os buracos na imagem
    preencher_buracos_pgm(&pgm, &pgmResultado);

	// Gravar a imagem resultante
	gravar_pgm(&pgmResultado, "saida_ruido.pgm");

	cout << "Processamento concluído EX01" << endl;

	// Liberar a memória alocada
    destruir_pgm(&pgm);
    destruir_pgm(&pgmResultado);

	/* cout << "\n\nEX3:\n";
	 list_r_ex3();*/

	/*cout << "\n\nEX4:\n";
	// Definir o ponto P em torno do qual as transformações serão realizadas
    float px = 350.0f;
    float py = 230.0f;

	// Ler a imagem PPM
    PPM imgOriginal;
	ler(&imgOriginal, "numeros_cor.ppm");

	// Criar uma nova imagem para armazenar o resultado
    PPM imgTransformada;
    criar(&imgTransformada, imgOriginal.larg, imgOriginal.alt);

	// Chamar a função que aplica as transformações
    aplicarTransformacoes(&imgOriginal, &imgTransformada, px, py);

	// Salvar a imagem transformada
    gravar(&imgTransformada, "saida.ppm");

	// Liberar memória
    destruir(&imgOriginal);
    destruir(&imgTransformada);

    cout << "Transformação concluída com sucesso. Imagem salva em 'saida.ppm'." << endl;*/
	
	cout << "Pressione uma tecla para encerrar o programa.\n";
	getchar();
	return EXIT_SUCCESS; 
}

vector<Vector3f> getTriangulo1() {

	// coordenadas dos pontos
	vector<Vector3f> v;
	v.push_back(Vector3f(4, 2, 1)); // A 
	v.push_back(Vector3f(8, 2, 1)); // B
	v.push_back(Vector3f(6, 7, 1)); // C

	return v;
}

void imprimeMFinal(vector<Vector3f> v, Matrix3f m) {
	for (size_t i = 0; i < v.size(); i++)
	{
		Vector3f resposta = m * v[i];

		cout << "Ponto " << i+1 << ": "<<  resposta.hnormalized().transpose() << endl;
	}
}

void lerEntrada (string entrada, Matrix3f *M, vector<Vector3f> *v) {
	stringstream strBuffer(entrada);
	
	string op;
	
	while(strBuffer >> op) {
		if (op == "T" || op == "R" || op == "E" || op == "CI" || op == "RE") {
			Matrix3f operationMatrix;

			//Translação
			if(op == "T") {
				
				float tx, ty;
				strBuffer >> tx;
				strBuffer >> ty;

				operationMatrix = getTranslacao(tx, ty);
			}
			//Rotação
			else if(op == "R") {
				
				float g;
				strBuffer >> g;
				
				operationMatrix = getRotacao(g);
			}
			//Escala
			else if(op == "E") {
				
				float sx, sy;
				strBuffer >> sx;
				strBuffer >> sy;
				
				operationMatrix = getEscala(sx ,sy);
			}
			//Cissalhamento
			else if(op == "CI") {
				
				string eixo;
				strBuffer >> eixo;
				if(eixo == "Y") {
					float b;
					strBuffer >> b;
					operationMatrix = getCissVertical(b);
				}
				else if(eixo == "X") {
					float a;
					strBuffer >> a;
					operationMatrix = getCissHorizontal(a);
				}
			}
			//Reflexão
			else if(op == "RE") {
				
				string eixo;
				strBuffer >> eixo;
				if(eixo == "Y") 
					operationMatrix = getReflexaoY();
				else if(eixo == "X") 
					operationMatrix = getReflexaoX();
				
			}

			*M = operationMatrix * (*M);
		}
		else {
			// Codigo para voltar 1 leitura do stream
			strBuffer.putback(' '); // Put back the space
			for (int i = op.length() - 1; i >= 0; --i) {
				strBuffer.putback(op[i]); // Put back the characters of the token
			}
			break; // Exit the loop to start reading point data
		}
	}


	float x,y;
	while(strBuffer >> x && strBuffer >> y) {

		v->push_back(Vector3f(x,y,1));
	}
}

void list_r_ex3() {
	string entrada = "T -2.5 -4 T 5 2 R 90 RE X T 2.5 4 2.5 7 4 5 4 1 1 1 1 5";

	Matrix3f M = Matrix3f::Identity();
	vector<Vector3f> v;

	lerEntrada(entrada, &M, &v);
	imprimeMFinal(v, M);
}

void aplicarTransformacoes(PPM* imgOriginal, PPM* imgTransformada, float px, float py) {
    // Matriz de transformação acumulada
    Matrix3f M = Matrix3f::Identity();

    // Passo 1: Transladar para que P seja a origem
    Matrix3f T1 = getTranslacao(-px, -py);
    M = T1 * M;

    // Passo 2: Escala com Sx=1 e Sy=0.5
    Matrix3f S1 = getEscala(1.0f, 0.5f);
    M = S1 * M;

    // Passo 3: Rotação de 45 graus
    Matrix3f R = getRotacao(45);
    M = R * M;

    // Passo 4: Escala com Sx=2 e Sy=2
    Matrix3f S2 = getEscala(2.0f, 2.0f);
    M = S2 * M;

    // Passo 5: Transladar de volta para a posição original
    Matrix3f T2 = getTranslacao(px, py);
    M = T2 * M;

    // Aplicar a transformação a cada pixel da imagem
    for (int y = 0; y < imgOriginal->alt; y++) {
        for (int x = 0; x < imgOriginal->larg; x++) {
            // Coordenadas homogêneas do pixel
            Vector3f p(static_cast<float>(x), static_cast<float>(y), 1.0f);

            // Aplicar a transformação
            Vector3f pTransformado = M * p;

            // Normalizar coordenadas homogêneas
            pTransformado /= pTransformado(2);

            // Obter as novas coordenadas
            int xNovo = static_cast<int>(round(pTransformado(0)));
            int yNovo = static_cast<int>(round(pTransformado(1)));

            // Verificar se as novas coordenadas estão dentro dos limites da imagem
            if (xNovo >= 0 && xNovo < imgTransformada->larg && yNovo >= 0 && yNovo < imgTransformada->alt) {
                // Obter a cor do pixel original
                RGB cor = getPixel(imgOriginal, x, y);
                // Definir a cor no pixel transformado
                setPixel(imgTransformada, xNovo, yNovo, cor);
            }
        }
    }
}

// AUX QUESTAO 1
// Função para obter os pixels vizinhos válidos de um pixel específico
vector<unsigned char> obter_vizinhos_validos(PGM *pgm, int x, int y) {
    vector<unsigned char> vizinhosValidos;

    // Coordenadas dos oito vizinhos
    int dx[] = {-1,  0,  1, -1, 1, -1,  0, 1};
    int dy[] = {-1, -1, -1,  0, 0,  1,  1, 1};

    // Obter os pixels vizinhos válidos
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // Verificar se o vizinho está dentro dos limites da imagem
        if (nx >= 0 && nx < pgm->larg && ny >= 0 && ny < pgm->alt) {
            unsigned char valorVizinho = getPixel_pgm(pgm, nx, ny);
            // Verificar se a intensidade do vizinho é diferente de zero
            if (valorVizinho != 0) {
                vizinhosValidos.push_back(valorVizinho);
            }
        }
    }
    return vizinhosValidos;
}

// Função para calcular a mediana de um vetor de valores
unsigned char calcular_mediana(vector<unsigned char> &valores) {
    // Ordenar os valores
    sort(valores.begin(), valores.end());

    double mediana;
    int n = valores.size();
    if (n % 2 == 1) {
        // Número ímpar de elementos
        mediana = valores[n / 2];
    } else {
        // Número par de elementos
        mediana = (valores[n / 2 - 1] + valores[n / 2]) / 2.0;
    }
    // Arredondar e converter para unsigned char
    return static_cast<unsigned char>(mediana + 0.5);
}

// Função para preencher os buracos na imagem usando a mediana dos vizinhos válidos
void preencher_buracos_pgm(PGM *pgmOriginal, PGM *pgmResultado) {
    // Percorrer cada pixel da imagem
    for (int y = 0; y < pgmOriginal->alt; y++) {
        for (int x = 0; x < pgmOriginal->larg; x++) {
            // Verificar se o pixel é um buraco (intensidade zero)
            if (getPixel_pgm(pgmOriginal, x, y) == 0) {
                vector<unsigned char> vizinhosValidos = obter_vizinhos_validos(pgmOriginal, x, y);

                // Verificar se existem vizinhos válidos
                if (!vizinhosValidos.empty()) {
                    // Calcular a mediana
                    unsigned char mediana = calcular_mediana(vizinhosValidos);
                    // Preencher o pixel com o valor da mediana
                    setPixel_pgm(pgmResultado, x, y, mediana);
                }
                // Se não houver vizinhos válidos, manter o pixel com intensidade zero
            }
        }
    }
}
// FIM AUX QUESTAO 1

// void lista3_exerc1_a() {

// 	vector<Vector3f> v = getTriangulo1();

// 	Matrix3f M = getTranslacao(0 ,3);

// 	imprimeMFinal(v, M);
// }

// void lista3_exerc1_b() {

// 	vector<Vector3f> v = getTriangulo1();

// 	Matrix3f M = getEscala(0.5f ,0.5f);

// 	imprimeMFinal(v, M);
// }

// void lista3_exerc1_c() {

// 	vector<Vector3f> v = getTriangulo1();

// 	Matrix3f M = getCissHorizontal(1.2f);

// 	imprimeMFinal(v, M);
// }

// void lista3_exerc1_d() {

// 	vector<Vector3f> v = getTriangulo1();

// 	Matrix3f M = getReflexaoX();

// 	imprimeMFinal(v, M);
// }

// void lista3_exerc1_e() {

// 	vector<Vector3f> v = getTriangulo1();

// 	Matrix3f M = getRotacao(-30);

// 	imprimeMFinal(v, M);
// }

// void lista3_exerc1_f() {

// 	vector<Vector3f> v = getTriangulo1();

// 	Matrix3f M = getTranslacao(6,4) * getRotacao(-30) * getTranslacao(-6,-4);

// 	imprimeMFinal(v, M);
// }

// void lista3_exerc1_g() {

// 	vector<Vector3f> v = getTriangulo1();

// 	Matrix3f M = getTranslacao(6,4) * getEscala(0.5f, 0.5f) * getTranslacao(-6,-4);

// 	imprimeMFinal(v, M);
// }

// void lista3_exerc1_h() {

// 	vector<Vector3f> v = getTriangulo1();

// 	Matrix3f M = getTranslacao(6,4) * getReflexaoY() * getTranslacao(3,-2) * getTranslacao(-6,-4);

// 	imprimeMFinal(v, M);
// }

// void lista3_exerc1_i() {

// 	vector<Vector3f> v = getTriangulo1();

// 	Matrix3f M = getTranslacao(6,4) * getTranslacao(2,0) * getEscala(0.5f, 1.0f) * getCissVertical(1.5f) * getTranslacao(-6,-4);

// 	imprimeMFinal(v, M);
// }

// void lista3_exerc2() {
	
// 	Matrix3f e = getEscala(1.5f, 0.5f);
// 	Matrix3f r = getRotacao(90.0f);
// 	Matrix3f t = getTranslacao(-6, 0);
// 	Matrix3f t_ = getTranslacao(4, 4);
// 	Matrix3f t_Inv = getTranslacao(-4, -4);

// 	Matrix3f M = t_ * t * r * e * t_Inv;

// 	vector<Vector3f> v;
// 	// cada push_back abaixo é um ponto
// 	v.push_back(Vector3f(2, 2, 1));
// 	v.push_back(Vector3f(6, 2, 1));
// 	v.push_back(Vector3f(6, 6, 1));
// 	v.push_back(Vector3f(2, 6, 1));

// 	for (size_t i = 0; i < v.size(); i++)
// 	{
// 		Vector3f resposta = M * v[i];

// 		cout << "Ponto " << i+1 << ": "<<  resposta.hnormalized().transpose() << endl;
// 	}
	
// }

// void lista3_exerc3() {
// 	vector<Vector3f> v;
// 	v.push_back(Vector3f(3, 2, 1));
// 	v.push_back(Vector3f(6, 2, 1));
// 	v.push_back(Vector3f(4.5, 6, 1));

// 	Matrix3f M = getTranslacao(4.5f,4.0f) * getTranslacao(0.5f, 0.0f) * getCissVertical(0.25f) * getRotacao(90) * getTranslacao(-4.5f,-4.0f);

// 	imprimeMFinal(v, M);
// }

// void lista4_exerc2() {

// 	string entrada1 = "R 45 4 1 7 3 6 6 2 7 1 4";
// 	string entrada2 = "T 5 2 4 1 7 3 6 6 2 7 1 4";

// 	Matrix3f M = Matrix3f::Identity();
// 	vector<Vector3f> v;

// 	cout << "Exemplo 1:" << endl;
// 	lerEntrada(entrada1, &M, &v);
// 	imprimeMFinal(v, M);

// 	Matrix3f M2 = Matrix3f::Identity();
// 	vector<Vector3f> v2;

// 	cout << "Exemplo 2:" << endl;
// 	lerEntrada(entrada2, &M2, &v2);
// 	imprimeMFinal(v2, M2);
// }

// void lista4_exerc3() {
// 	string entrada = "T -4 -4 R 90 T 4 4 2 2 6 2 4 6";
// 	string entrada2 = "T -4 -4 E 1.5 1.5 T 4 4 2 2 6 2 4 6";

// 	Matrix3f M = Matrix3f::Identity();
// 	vector<Vector3f> v;

// 	cout << "Exemplo 1:" << endl;
// 	lerEntrada(entrada, &M, &v);
// 	imprimeMFinal(v, M);

// 	Matrix3f M2 = Matrix3f::Identity();
// 	vector<Vector3f> v2;

// 	cout << "Exemplo 2:" << endl;
// 	lerEntrada(entrada2, &M2, &v2);
// 	imprimeMFinal(v2, M2);
// }