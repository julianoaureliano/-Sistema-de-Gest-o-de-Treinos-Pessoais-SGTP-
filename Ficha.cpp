#include "Ficha.h"
#include <iostream>
#include <iomanip>
using namespace std;
int Ficha::proximoId = 1;

// Construtor para novos cadastros
Ficha::Ficha(string nome)
{
    // Implementar
    this->nome = nome;
    this->id = proximoId++;
}

// Construtor para leitura de arquivo
Ficha::Ficha(int id, string nome)
{
    // Implementar
    this->id = id;
    this->nome = nome;

    if (id >= proximoId)
    {
        proximoId = id + 1;
    }
}

// Destrutor (não deletar exercícios, apenas limpar vector)
Ficha::~Ficha()
{
    // Implementar
    exercicios.clear();
}

// Adicionar exercício à ficha
void Ficha::adicionarExercicio(Exercicio *exercicio)
{
    // Implementar
    if (exercicio != nullptr)
    {
        exercicios.push_back(exercicio);
    }
}

// Exibir ficha completa com exercícios e totais
void Ficha::exibirFicha() const
{
    // Implementar
    cout << "\n== Ficha de Treino: " << nome << " (ID: " << id << ") ===" << endl;

    if (exercicios.empty())
    {
        cout << "Esta ficha ainda não possui exercícios." << endl;
    }
    else
    {
        cout << "Exercícios:" << endl;
        for (const auto &exercicio : exercicios)
        {
            exercicio->exibirDetalhes(); // polimorfismo
        }
    }

    cout << "-- Resumo da Ficha ---" << endl;
    cout << fixed << setprecision(1);
    cout << " - Tempo Total Estimado: " << calcularTempoTotal() << " minutos" << endl;
    cout << " - Calorias Totais Estimadas: " << calcularCaloriasTotais() << " kcal" << endl;
    cout << "--------------------" << endl;
}

// Calcular tempo total da ficha
double Ficha::calcularTempoTotal() const
{
    double total = 0.0;
    for (const auto &exercicio : exercicios)
    {
        total += exercicio->calcularTempoEstimado(); // Polimorfismo
    }
    return total;
}

// Calcular calorias totais da ficha
double Ficha::calcularCaloriasTotais() const
{
    double total = 0.0;
    for (const auto &exercicio : exercicios)
    {
        total += exercicio->calcularCaloriasGastas(); // Polimorfismo
    }
    return total;
}

// Getters
int Ficha::getId() const
{
    return id; // Implementar
}

string Ficha::getNome() const
{
    return nome; // Implementar
}

const vector<Exercicio *> &Ficha::getExercicios() const
{
    static vector<Exercicio *> vazio; // Placeholder para compilar
    return exercicios;
}

// Atualizar próximo ID
void Ficha::atualizarProximoId(int maiorId)
{
    // Implementar
    if (maiorId >= proximoId)
    {
        proximoId = maiorId + 1;
    }
}
