#include "Historico.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#define arquivo_historico "historico.txt" // mudar para futuros testes ou uso de outro arquivo

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
    cout << "\n--- HISTORICO DE EXECUCOES (" << registros.size() << " total) ---" << endl;
    if (registros.empty())
    {
        cout << "Nenhum registro de execucao no historico." << endl;
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
    registros.clear(); // Limpa dados existentes
    ifstream arquivo(arquivo_historico);
    string linha;

    if (!arquivo.is_open())
    {
        // cerr << "AVISO: Arquivo historico.txt não encontrado. Começando com histórico vazio." << endl;
        return;
    }

    while (getline(arquivo, linha))
    {
        if (linha.empty())
            continue;

        RegistroTreino novoRegistro;
        stringstream ss(linha);
        string token;
        int campo = 0;

        try
        {
            // Formato: DATA;ID_FICHA;NOME_FICHA;TEMPO_TOTAL;CALORIAS_TOTAL

            // 1. DATA
            getline(ss, token, ';');
            if (token.empty())
                throw runtime_error("Campo DATA vazio.");
            novoRegistro.dataHora = token;

            // 2. ID_FICHA
            getline(ss, token, ';');
            novoRegistro.idFicha = stoi(token);

            // 3. NOME_FICHA
            getline(ss, token, ';');
            if (token.empty())
                throw runtime_error("Campo NOME_FICHA vazio.");
            novoRegistro.nomeFicha = token;

            // 4. TEMPO_TOTAL
            getline(ss, token, ';');
            novoRegistro.tempoTotal = stod(token);

            // 5. CALORIAS_TOTAL
            getline(ss, token, ';');
            novoRegistro.caloriasTotal = stod(token);

            registros.push_back(novoRegistro);
        }
        catch (const exception &e)
        {
            cerr << "Erro ao carregar linha do historico.txt: " << e.what() << " Linha ignorada: " << linha << endl;
            continue;
        }
    }
    arquivo.close();
}

// Salvar histórico no arquivo
void Historico::salvarEmArquivo() const
{
    // Implementar
    ofstream arquivo(arquivo_historico);

    if (!arquivo.is_open())
    {
        cerr << "Erro: Nao foi possivel abrir historico.txt para salvar." << endl;
        return;
    }

    // Formato: DATA;ID_FICHA;NOME_FICHA;TEMPO_TOTAL;CALORIAS_TOTAL
    for (const auto &registro : registros)
    {
        arquivo << registro.dataHora << ";"
                << registro.idFicha << ";"
                << registro.nomeFicha << ";"
                << fixed << setprecision(2) << registro.tempoTotal << ";"
                << fixed << setprecision(2) << registro.caloriasTotal << endl;
    }

    arquivo.close();
}
