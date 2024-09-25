#include <iostream>
#include "transformation.hpp"
#include <Eigen/Dense>
#include <vector>

using namespace std;
using namespace Eigen;

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

int main(void)
{

	// Matrix3f t = Matrix3f::Identity();
	// t(0,2) = 3;
	// t(1,2) = -2;
	// cout << t << endl << endl;

	// Vector3f ponto1(10, 12, 1);
	// cout << ponto1 << endl << endl;
	
	// Vector3f resposta = t * ponto1;
	// cout << resposta << endl << endl;
	// cout << resposta.transpose() << endl << endl;
	
	// Vector2f respostaNormalizada = resposta.hnormalized();
	// cout << respostaNormalizada.transpose() << endl << endl;

	lista3_exerc2();

	cout << "Pressione uma tecla para encerrar o programa.\n";
	getchar();
	return EXIT_SUCCESS; 
}