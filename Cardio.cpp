#include "Cardio.h"
#include <iostream>
#include <iomanip> // setprecision
using namespace std;
// Construtor para novos cadastros
Cardio::Cardio(string nome, int duracao, double caloriasPorMinuto)
    : Exercicio(nome)
{
    // Implementar
    this->duracao = duracao;
    this->caloriasPorMinuto = caloriasPorMinuto;
}

// Construtor para leitura de arquivo
Cardio::Cardio(int id, string nome, bool ativo, int duracao, double caloriasPorMinuto)
    : Exercicio(id, nome, ativo)
{
    // Implementar
    this->duracao = duracao;
    this->caloriasPorMinuto = caloriasPorMinuto;
}

// Exibir detalhes do exercício
void Cardio::exibirDetalhes() const
{
    // Implementar
    cout << fixed << setprecision(1);
    cout << "  - ID: " << getId() << " | Nome: " << getNome() << " | Tipo: Cardio" << (isAtivo() ? "" : " (INATIVO)") << endl;
    cout << "    - Duracao: " << duracao << " min" << endl;
    cout << "    - Cal./min: " << caloriasPorMinuto << " kcal" << endl;
    cout << "    - Estimativa: " << calcularTempoEstimado() << " min / " << calcularCaloriasGastas() << " kcal" << endl;
}

// Calcular tempo estimado (duração em minutos)
double Cardio::calcularTempoEstimado() const
{
    return (double)duracao;
}

// Calcular calorias gastas
double Cardio::calcularCaloriasGastas() const
{
    return duracao * caloriasPorMinuto;
}

// Retornar tipo do exercício (1 = Cardio)
int Cardio::getTipo() const
{
    return 1;
}

// Getter de duração
int Cardio::getDuracao() const
{
    return duracao;
}

// Getter de calorias por minuto
double Cardio::getCaloriasPorMinuto() const
{
    return caloriasPorMinuto;
}
