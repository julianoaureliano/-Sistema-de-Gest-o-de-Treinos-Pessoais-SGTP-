#include "Forca.h"
#include <iostream>
#include <iomanip> // setprecision
using namespace std;

// Construtor para novos cadastros
Forca::Forca(string nome, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(nome)
{
    // Implementar
    this->carga = carga;
    this->series = series;
    this->repeticoes = repeticoes;
    this->tempoDescanso = tempoDescanso;
}

// Construtor para leitura de arquivo
Forca::Forca(int id, string nome, bool ativo, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(id, nome, ativo)
{
    // Implementar
    this->carga = carga;
    this->series = series;
    this->repeticoes = repeticoes;
    this->tempoDescanso = tempoDescanso;
}

// Exibir detalhes do exercício
void Forca::exibirDetalhes() const
{
    // Implementar
    cout << fixed << setprecision(1);
    cout << "  - ID: " << getId() << " | Nome: " << getNome() << " | Tipo: Forca" << (isAtivo() ? "" : " (INATIVO)") << endl;
    cout << "    - Carga: " << carga << " kg" << " | Series: " << series << " | Repeticoes: " << repeticoes << " | Descanso: " << tempoDescanso << " seg" << endl;
    cout << "    - Estimativa: " << calcularTempoEstimado() << " min / " << calcularCaloriasGastas() << " kcal" << endl;
}

// Calcular tempo estimado (em minutos)
double Forca::calcularTempoEstimado() const
{
    // segundos: (Séries * Repetições * 3s) + (Séries * Tempo de Descanso)
    double tempoSegundos = (series * repeticoes * 3.0) + (series * tempoDescanso);
    // converte para min
    return tempoSegundos / 60.0;
}

// Calcular calorias gastas (Carga * Séries * Repetições / 100)
double Forca::calcularCaloriasGastas() const
{
    return (carga * series * repeticoes) / 100.0;
}

// Retornar tipo do exercício (2 = Força)
int Forca::getTipo() const
{
    return 2; // Implementar
}

// Getters
double Forca::getCarga() const
{
    return carga; // Implementar
}

int Forca::getSeries() const
{
    return series; // Implementar
}

int Forca::getRepeticoes() const
{
    return repeticoes; // Implementar
}

int Forca::getTempoDescanso() const
{
    return tempoDescanso; // Implementar
}
