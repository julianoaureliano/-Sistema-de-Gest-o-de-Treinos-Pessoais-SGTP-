#include "Sistema.h"
#include "Cardio.h"
#include "Forca.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <iomanip>
using namespace std;
// nomes dos arquivos
#define ARQUIVO_EXERCICIOS "exercicios.txt"
#define ARQUIVO_FICHAS "fichas.txt"

Sistema::Sistema()
{
    carregarDados();
}

Sistema::~Sistema()
{
    salvarDados();

    // deletar ponteiros de exercicios
    for (auto &ex : exercicios)
    {
        delete ex;
    }
    exercicios.clear();

    // deletar ponteiros de fichas
    for (auto &f : fichas)
    {
        delete f;
    }
    fichas.clear();

    // historico é destruído automaticamente
}

// Carregar dados dos arquivos
void Sistema::carregarDados()
{
    // Carregar exercicios.txt
    ifstream arqEx(ARQUIVO_EXERCICIOS);
    string linhaEx;
    int maxIdEx = 0;

    if (arqEx.is_open())
    {
        while (getline(arqEx, linhaEx))
        {
            if (linhaEx.empty())
                continue;

            stringstream ss(linhaEx);
            string token;
            int tipo, id;
            string nome;
            int ativoInt; // 1 ou 0

            // formato: tipo;id;nome;ativo[parametro]
            try
            {
                // tipo
                getline(ss, token, ';');
                tipo = stoi(token);
                // id
                getline(ss, token, ';');
                id = stoi(token);
                // nome
                getline(ss, token, ';');
                nome = token;
                // ativo
                getline(ss, token, ';');
                ativoInt = stoi(token);
                bool ativo = (ativoInt == 1);

                Exercicio *novoEx = nullptr;

                if (tipo == 1)
                { // cardio
                    int duracao;
                    double caloriasPorMinuto;
                    getline(ss, token, ';');
                    duracao = stoi(token);
                    getline(ss, token, ';');
                    caloriasPorMinuto = stod(token);
                    novoEx = new Cardio(id, nome, ativo, duracao, caloriasPorMinuto);
                }
                else if (tipo == 2)
                { // força
                    double carga;
                    int series, repeticoes, tempoDescanso;
                    getline(ss, token, ';');
                    carga = stod(token);
                    getline(ss, token, ';');
                    series = stoi(token);
                    getline(ss, token, ';');
                    repeticoes = stoi(token);
                    getline(ss, token, ';');
                    tempoDescanso = stoi(token);
                    novoEx = new Forca(id, nome, ativo, carga, series, repeticoes, tempoDescanso);
                }

                if (novoEx)
                {
                    exercicios.push_back(novoEx);
                    if (id > maxIdEx)
                        maxIdEx = id;
                }
            }
            catch (const exception &e)
            {
                cerr << "Erro ao carregar linha do exercicios.txt: " << e.what() << " Linha ignorada: " << linhaEx << endl;
            }
        }
        arqEx.close();
        Exercicio::atualizarProximoId(maxIdEx);
    }

    // Carregar fichas.txt
    ifstream arqFichas(ARQUIVO_FICHAS);
    string linhaFicha;
    int maxIdFicha = 0;

    if (arqFichas.is_open())
    {
        while (getline(arqFichas, linhaFicha))
        {
            if (linhaFicha.empty())
                continue;

            stringstream ss(linhaFicha);
            string token;
            int idFicha, totalExercicios;
            string nomeFicha;

            // formato: id_ficha;nome_ficha;total_exercicios;id_ex_1..
            try
            {
                // id_ficha
                getline(ss, token, ';');
                idFicha = stoi(token);
                // nome_ficha
                getline(ss, token, ';');
                nomeFicha = token;
                // total_exercicios
                getline(ss, token, ';');
                totalExercicios = stoi(token);

                Ficha *novaFicha = new Ficha(idFicha, nomeFicha);

                for (int i = 0; i < totalExercicios; ++i)
                {
                    getline(ss, token, ';');
                    int idExercicio = stoi(token);
                    Exercicio *ex = buscarExercicioPorId(idExercicio);
                    if (ex)
                    {
                        novaFicha->adicionarExercicio(ex);
                    }
                    else
                    {
                        cerr << "Aviso: Exercicio ID " << idExercicio << " na Ficha ID " << idFicha << " nao foi encontrado e foi ignorado." << endl;
                    }
                }

                fichas.push_back(novaFicha);
                if (idFicha > maxIdFicha)
                    maxIdFicha = idFicha;
            }
            catch (const exception &e)
            {
                cerr << "Erro ao carregar linha do fichas.txt: " << e.what() << " Linha ignorada: " << linhaFicha << endl;
            }
        }
        arqFichas.close();
        Ficha::atualizarProximoId(maxIdFicha);
    }

    historico.carregarDeArquivo();
}

// Salvar dados nos arquivos
void Sistema::salvarDados()
{
    // Salvar exercicios.txt

    ofstream arqEx(ARQUIVO_EXERCICIOS);
    if (!arqEx.is_open())
    {
        cerr << "Erro: Nao foi possivel abrir exercicios.txt para salvar." << endl;
        return;
    }

    // formato: tipo;id;nome;ativo[parametro]
    for (const auto &ex : exercicios)
    {
        // campos communs
        arqEx << ex->getTipo() << ";"
              << ex->getId() << ";"
              << ex->getNome() << ";"
              << (ex->isAtivo() ? 1 : 0) << ";"; // ATIVO: 1 ou 0

        // campos especificos (polimorfismo)
        if (ex->getTipo() == 1)
        { // cardio
            Cardio *c = static_cast<Cardio *>(ex);
            arqEx << c->getDuracao() << ";"
                  << fixed << setprecision(2) << c->getCaloriasPorMinuto();
        }
        else if (ex->getTipo() == 2)
        { // força
            Forca *f = static_cast<Forca *>(ex);
            arqEx << fixed << setprecision(2) << f->getCarga() << ";"
                  << f->getSeries() << ";"
                  << f->getRepeticoes() << ";"
                  << f->getTempoDescanso();
        }
        arqEx << endl;
    }
    arqEx.close();

    // Salvar fichas.txt
    ofstream arqFichas(ARQUIVO_FICHAS);
    if (!arqFichas.is_open())
    {
        cerr << "Erro: Nao foi possivel abrir fichas.txt para salvar." << endl;
        return;
    }

    // formato: id_ficha;nome_ficha;total_exercicios;id_ex_1..
    for (const auto &f : fichas)
    {
        const auto &listaEx = f->getExercicios();
        arqFichas << f->getId() << ";"
                  << f->getNome() << ";"
                  << listaEx.size();

        for (const auto &ex : listaEx)
        {
            arqFichas << ";" << ex->getId();
        }
        arqFichas << endl;
    }
    arqFichas.close();

    historico.salvarEmArquivo();
}

// Buscar exercício por ID
Exercicio *Sistema::buscarExercicioPorId(int id)
{
    for (Exercicio *ex : exercicios)
    {
        if (ex->getId() == id)
        {
            return ex;
        }
    }
    return nullptr;
}

// Buscar ficha por ID
Ficha *Sistema::buscarFichaPorId(int id)
{
    for (Ficha *f : fichas)
    {
        if (f->getId() == id)
        {
            return f;
        }
    }
    return nullptr;
}
// função  para pegar entrada de inteiro para nao dar pau no programa
int capturarInt(const string &prompt)
{
    int valor;
    cout << prompt;
    while (!(cin >> valor))
    {
        cout << "Entrada invalida. Digite um numero inteiro: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpa buffer para nao dar bugs
    return valor;
}

// Função para pegar entrada de double para nao dar pau no programa
double capturarDouble(const string &prompt)
{
    double valor;
    cout << prompt;
    while (!(cin >> valor))
    {
        cout << "Entrada invalida. Digite um numero decimal: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpa buffer para nao dar bugs
    return valor;
}
// Cadastrar novo exercício
void Sistema::cadastrarExercicio()
{
    // Implementar
    limparTela();
    string nome;
    int tipo;

    cout << "-- CADASTRO DE NOVO EXERCICIO ---" << endl;
    cout << "Nome do Exercicio: ";
    getline(cin, nome);

    tipo = capturarInt("Tipo (1 - Cardio, 2 - Força): ");

    if (tipo == 1)
    {
        int duracao = capturarInt("Duracao padrao (minutos): ");
        double caloriasPorMinuto = capturarDouble("Calorias estimadas por minuto (kcal/min): ");

        Exercicio *novoCardio = new Cardio(nome, duracao, caloriasPorMinuto);
        exercicios.push_back(novoCardio);
        cout << "X Cardio '" << nome << "' (ID: " << novoCardio->getId() << ") cadastrado." << endl;
    }
    else if (tipo == 2)
    {
        double carga = capturarDouble("Carga padrao (kg): ");
        int series = capturarInt("Numero de Series: ");
        int repeticoes = capturarInt("Numero de Repeticoes: ");
        int tempoDescanso = capturarInt("Tempo de Descanso (segundos): ");

        Exercicio *novaForca = new Forca(nome, carga, series, repeticoes, tempoDescanso);
        exercicios.push_back(novaForca);
        cout << "V Forca '" << nome << "' (ID: " << novaForca->getId() << ") cadastrada." << endl;
    }
    else
    {
        cout << "X Tipo de exercício invalido. Cadastro cancelado." << endl;
        pausar();
        return;
    }

    salvarDados();
    pausar();
}

// Listar exercícios ativos
void Sistema::listarExercicios()
{
    // Implementar
    limparTela();
    cout << "-- LISTA DE EXERCICIOS ATIVOS (" << exercicios.size() << " total) ---" << endl;
    bool ativoEncontrado = false;

    for (const auto &ex : exercicios)
    {
        if (ex->isAtivo())
        {
            ex->exibirDetalhes();
            ativoEncontrado = true;
        }
    }

    if (!ativoEncontrado)
    {
        cout << "Nenhum exercicio ativo encontrado." << endl;
    }
    cout << "-----------------------------------------------" << endl;
    pausar();
}

// Desativar exercício
void Sistema::excluirExercicio()
{
    // Implementar
    limparTela();
    listarExercicios();

    if (exercicios.empty())
    {
        cout << "Nao tem exercícios para excluir." << endl;
        pausar();
        return;
    }

    int id = capturarInt("Digite o ID do exercício a ser desativado: ");
    Exercicio *ex = buscarExercicioPorId(id);

    if (ex)
    {
        if (ex->isAtivo())
        {
            ex->desativar();
            cout << "V Exercicio '" << ex->getNome() << "' (ID: " << id << ") desativado com sucesso." << endl;
            salvarDados();
        }
        else
        {
            cout << "AVISO: Exercicio '" << ex->getNome() << "' (ID: " << id << ") ja estava inativo." << endl;
        }
    }
    else
    {
        cout << "X Exercicio com ID " << id << " nao encontrado." << endl;
    }
    pausar();
}

// Criar nova ficha
void Sistema::criarFicha()
{
    // Implementar
}

// Adicionar exercício à ficha
void Sistema::adicionarExercicioFicha()
{
    // Implementar
}

// Listar todas as fichas
void Sistema::listarFichas()
{
    // Implementar
}

// Registrar treino realizado
void Sistema::registrarTreino()
{
    // Implementar
}

// Exibir histórico de treinos
void Sistema::exibirHistorico()
{
    // Implementar
}
