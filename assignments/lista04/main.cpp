#include <iostream>
#include "transformation.hpp"
#include <Eigen/Dense>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
using namespace Eigen;

vector<Vector3f> getTriangulo1();
void imprimeMFinal(vector<Vector3f> v, Matrix3f m);
void lerEntrada(string entrada, Matrix3f M, vector<Vector3f> v);

void lista3_exerc1_a();
void lista3_exerc1_b();
void lista3_exerc1_c();
void lista3_exerc1_d();
void lista3_exerc1_e();
void lista3_exerc1_f();
void lista3_exerc1_g();
void lista3_exerc1_h();
void lista3_exerc1_i();
void lista3_exerc2();
void lista3_exerc3();

void lista4_exerc2() {

	string entrada = "T 4 2 4 1 7 3 5 2";
	Matrix3f M = Matrix3f::Identity();
	vector<Vector3f> v;

	lerEntrada(entrada, M, v);
}

int main(void)
{
	setlocale(LC_ALL, "pt_BR.UTF-8");

	// cout << "######LISTA03######" << endl;
	// cout << "Exerc 1.a: " << endl;
	// lista3_exerc1_a();

	// cout << endl << "Exerc 1.b: " << endl;
	// lista3_exerc1_b();

	// cout << endl << "Exerc 1.c: " << endl;
	// lista3_exerc1_c();

	// cout << endl << "Exerc 1.d: " << endl;
	// lista3_exerc1_d();
	
	// cout << endl << "Exerc 1.e: " << endl;
	// lista3_exerc1_e();
	
	// cout << endl << "Exerc 1.f: " << endl;
	// lista3_exerc1_f();
	
	// cout << endl << "Exerc 1.g: " << endl;
	// lista3_exerc1_g();

	// cout << endl << "Exerc 1.h: " << endl;
	// lista3_exerc1_h();
	
	// cout << endl << "Exerc 1.i: " << endl;
	// lista3_exerc1_i();

	// cout << endl << "Exerc 2: " << endl;
	// lista3_exerc2();

	// cout << endl << "Exerc 3: " << endl;
	// lista3_exerc3();

	cout << "######LISTA04######" << endl;
	cout << endl << "Exerc 2: " << endl;
	lista4_exerc2();
	
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

void lerEntrada (string entrada, Matrix3f M, vector<Vector3f> v) {
	stringstream strBuffer(entrada);
	
	string op;
	strBuffer >> op;


	//Translação
	if(op == "T") {
		
		float tx, ty;
		strBuffer >> tx;
		strBuffer >> ty;

		M = getTranslacao(tx, ty);
	}
	//Rotação
	else if(op == "R") {
		
		float g;
		strBuffer >> g;
		
		M = getRotacao(g);
	}
	//Escala
	else if(op == "E") {
		
		float sx, sy;
		strBuffer >> sx;
		strBuffer >> sy;
		
		M = getEscala(sx ,sy);
	}
	//Cissalhamento
	else if(op == "CI") {
		
		string eixo;
		strBuffer >> eixo;
		if(eixo == "Y") {
			float b;
			strBuffer >> b;
			M = getCissVertical(b);
		}
		else if(eixo == "X") {
			float a;
			strBuffer >> a;
			M = getCissHorizontal(a);
		}
	}
	//Reflexão
	else if(op == "RE") {
		
		string eixo;
		strBuffer >> eixo;
		if(eixo == "Y") {
			M = getReflexaoY();
		}
		else if(eixo == "X") {
			M = getReflexaoX();
		}
	}

	float x,y;
	while(strBuffer >> x && strBuffer >> y) {

		v.push_back(Vector3f(x,y,1));
	}
}

void lista3_exerc1_a() {

	vector<Vector3f> v = getTriangulo1();

	Matrix3f M = getTranslacao(0 ,3);

	imprimeMFinal(v, M);
}

void lista3_exerc1_b() {

	vector<Vector3f> v = getTriangulo1();

	Matrix3f M = getEscala(0.5f ,0.5f);

	imprimeMFinal(v, M);
}

void lista3_exerc1_c() {

	vector<Vector3f> v = getTriangulo1();

	Matrix3f M = getCissHorizontal(1.2f);

	imprimeMFinal(v, M);
}

void lista3_exerc1_d() {

	vector<Vector3f> v = getTriangulo1();

	Matrix3f M = getReflexaoX();

	imprimeMFinal(v, M);
}

void lista3_exerc1_e() {

	vector<Vector3f> v = getTriangulo1();

	Matrix3f M = getRotacao(-30);

	imprimeMFinal(v, M);
}

void lista3_exerc1_f() {

	vector<Vector3f> v = getTriangulo1();

	Matrix3f M = getTranslacao(6,4) * getRotacao(-30) * getTranslacao(-6,-4);

	imprimeMFinal(v, M);
}

void lista3_exerc1_g() {

	vector<Vector3f> v = getTriangulo1();

	Matrix3f M = getTranslacao(6,4) * getEscala(0.5f, 0.5f) * getTranslacao(-6,-4);

	imprimeMFinal(v, M);
}

void lista3_exerc1_h() {

	vector<Vector3f> v = getTriangulo1();

	Matrix3f M = getTranslacao(6,4) * getReflexaoY() * getTranslacao(3,-2) * getTranslacao(-6,-4);

	imprimeMFinal(v, M);
}

void lista3_exerc1_i() {

	vector<Vector3f> v = getTriangulo1();

	Matrix3f M = getTranslacao(6,4) * getTranslacao(2,0) * getEscala(0.5f, 1.0f) * getCissVertical(1.5f) * getTranslacao(-6,-4);

	imprimeMFinal(v, M);
}

void lista3_exerc2() {
	
	Matrix3f e = getEscala(1.5f, 0.5f);
	Matrix3f r = getRotacao(90.0f);
	Matrix3f t = getTranslacao(-6, 0);
	Matrix3f t_ = getTranslacao(4, 4);
	Matrix3f t_Inv = getTranslacao(-4, -4);

	Matrix3f M = t_ * t * r * e * t_Inv;

	vector<Vector3f> v;
	// cada push_back abaixo é um ponto
	v.push_back(Vector3f(2, 2, 1));
	v.push_back(Vector3f(6, 2, 1));
	v.push_back(Vector3f(6, 6, 1));
	v.push_back(Vector3f(2, 6, 1));

	for (size_t i = 0; i < v.size(); i++)
	{
		Vector3f resposta = M * v[i];

		cout << "Ponto " << i+1 << ": "<<  resposta.hnormalized().transpose() << endl;
	}
	
}

void lista3_exerc3() {
	vector<Vector3f> v;
	v.push_back(Vector3f(3, 2, 1));
	v.push_back(Vector3f(6, 2, 1));
	v.push_back(Vector3f(4.5, 6, 1));

	Matrix3f M = getTranslacao(4.5f,4.0f) * getTranslacao(0.5f, 0.0f) * getCissVertical(0.25f) * getRotacao(90) * getTranslacao(-4.5f,-4.0f);

	imprimeMFinal(v, M);
}