#include "Historico.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;
// Adicionar registro ao histórico
void Historico::adicionarRegistro(const RegistroTreino &registro)
{
    // Implementar
    registros.push_back(registro);
}

// Exibir histórico completo
void Historico::exibirHistorico() const
{
    // Implementar
    cout << "\n--- HISTÓRICO DE EXECUCOES (" << registros.size() << " total) ---" << endl;
    if (registros.empty())
    {
        cout << "Nenhum registro de execucao no histórico." << endl;
    }
    else
    {
        for (const auto &registro : registros)
        {
            cout << "\n- Data/Hora: " << registro.dataHora << endl;
            cout << "  - Ficha: " << registro.nomeFicha << " (ID: " << registro.idFicha << ")" << endl;
            cout << fixed << setprecision(1);
            cout << "  - Tempo Gasto (Real): " << registro.tempoTotal << " minutos" << endl;
            cout << "  - Calorias Gastas (Real): " << registro.caloriasTotal << " kcal" << endl;
        }
    }
    cout << "-----------------------------------------------" << endl;
}

// Getter de registros
const vector<RegistroTreino> &Historico::getRegistros() const
{
    static vector<RegistroTreino> vazio; // Placeholder para compilar
    return registros;
}

// Carregar histórico do arquivo
void Historico::carregarDeArquivo()
{
    // Implementar
}

// Salvar histórico no arquivo
void Historico::salvarEmArquivo() const
{
    // Implementar
}
