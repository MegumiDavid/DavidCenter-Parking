#include <mysql.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <locale.h>
#include <string>

//declarando variaveis para acesso do bd
char* usr = (char*)"root";
char* pass = (char*)"******";
char* db = (char*)"DavidCenter";

int qstado;

MYSQL mysql, * conn;
MYSQL_RES result;
MYSQL_ROW linha;
//estado do query.
int qstate;

//conecta com banco de dados e imprime "VAGAS"
void imprime_bd()
{
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", usr, pass, db, 3306, NULL, 0);

    if (conn) {
        puts("Conexao com o Banco de Dados bem sucedida!");

        std::string query = "SELECT * FROM VAGAS";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (linha = mysql_fetch_row(res))
            {
                printf("ID: %s, Status: %s\n", linha[0], linha[1]);
            }
        }
        else
        {
            std::cout << "Query falhou: " << mysql_error(conn) << std::endl;
        }
    }
    else {
        puts("Falha ao conectar com o Banco de dados!");
    }

}

int insere_vaga(std::string id_vaga, int status_vaga)
{
    mysql_init(&mysql);
    std::string instrucao = "UPDATE Vagas SET STATUS_VAGA = " + std::to_string(status_vaga) + " WHERE CODIGO_VAGA = '" + id_vaga + "';";
    conn = mysql_real_connect(&mysql, "localhost", usr, pass, db, 0, NULL, 0);

    if (conn == NULL)
    {
        std::cout << mysql_error(&mysql) << std::endl;
    }
   
    else
    {
        (mysql_query(&mysql, instrucao.c_str()));
        if (qstado != 0) 
        {
            std::cout << mysql_error(conn) << std::endl;
            return 1;
        }
    }
        mysql_close(&mysql);
    }

//funcao que valida int
template<typename t>
void valida_input(t& input, const std::string msg)
{
    //impede casos de cin.fail (so por precaucao):
    std::cout << msg;
    std::cin >> input;
    while (std::cin.fail())
    {
        std::cout << "\n>> Erro de entrada, tente novamente.\n";
        std::cin.clear();
        std::cin.ignore(9999, '\n');
        std::cout << msg;
        std::cin >> input;
    }
}

//funcao do menu de opcoes (impressao e entrada)
void menu_de_opcoes(int& opcao_menu)
{
    std::cout << "\nMenu de opcoes\n\n";
    std::cout << "1 - Inserir vagas aleatorias\n";
    std::cout << "2 - Inserir '0' em todas as vagas\n";
    std::cout << "3 - Inserir '1' em todas as vagas\n";
    std::cout << "4 - Alterar vagas existentes\n";
    std::cout << "5 - Imprimir mapa de vagas\n";
    std::cout << "0 - Sair do programa\n";
    //validacao de entrada do menu:
    do {
        valida_input(opcao_menu, "\nDigite a opcao: ");
        if (opcao_menu < 0 || opcao_menu > 5) std::cout << "\n>>Insira apenas valores existentes no menu!\n";
    } while (opcao_menu < 0 || opcao_menu > 5);

}

void seleciona_todas_vagas(int opcao)
{
    int x, i, j, andar, vaga=0;
    char letra;
    std::string idvaga;

    srand((unsigned)time(0));       //seed do numero gerado aleatoreamente 

    for (x = 0; x < 5; x++)
    {
        andar = (x + 1);
        for (i=0; i<4; i++)
        {
            switch (i)
            {
                case 0:
                    letra = 'A';
                    break;               
                case 1:
                    letra = 'B';
                    break;                
                case 2:
                    letra = 'C';
                    break;
                case 3:
                    letra = 'D';
                    break;
            }
            
            for (j = 0; j < 15; j++) 
            {
                if (j < 9) idvaga = std::to_string(andar) + letra + '0' + std::to_string(j + 1);
                else idvaga = std::to_string(andar) + letra + std::to_string(j + 1);
                if (opcao==1) insere_vaga(idvaga, (rand() % 2));
                if (opcao==2)insere_vaga(idvaga, 0);
                if (opcao == 3)insere_vaga(idvaga, 1);
                //std::cout << std::endl << idvaga;
            }
        }

    }
    std::cout << "\n>>Vagas alteradas com sucesso!\n";
}

void alterar()
{
    int n_andar, vaga, valor;
    char bloco;
    std::string id_vaga;
    do
    {
        valida_input(n_andar, "Alterar vaga em qual andar? ");
        if (n_andar < 1 || n_andar > 5) std::cout << "\n>>Insira apenas valores entre 1 e 5!\n";
    } while (n_andar < 1 || n_andar > 5);
    do
    {
        valida_input(bloco, "Alterar vaga em qual bloco? ");
        bloco = toupper(bloco);
        if (bloco < 'A' || bloco>'D') std::cout << "\n>>Insira apenas letras de 'A' a 'D'!\n";     
    } while (bloco < 'A' || bloco>'D');
    do
    {
        valida_input(vaga, "Alterar qual vaga (1-15)? ");
        if (vaga < 1 || vaga>15) std::cout << "\n>>Insira apenas letras de 'A' a 'D'!\n";
    } while (vaga < 1 || vaga>15);
    do
    {
        valida_input(valor, "Inserir qual valor na vaga? ");
        if (valor < 0 || valor > 1) std::cout << "\n>>Insira apenas valores entre 1 e 5!\n";
    } while (valor < 0 || valor > 1);

    if (vaga<10) id_vaga = std::to_string(n_andar) + bloco + '0' + std::to_string(vaga);
    else id_vaga = std::to_string(n_andar) + bloco + std::to_string(vaga);
    insere_vaga(id_vaga, valor);
    std::cout << "\n>>Vaga alterada com sucesso!\n";
}

int main()
{
    int opcao, n, n_procurar, x, conta = 0;

    do
    {
        //imprime menu
        menu_de_opcoes(opcao);

        switch (opcao)
        {
        case 1:
            seleciona_todas_vagas(opcao);
            break;
        case 2:
            seleciona_todas_vagas(opcao);
            break;
        case 3:
            seleciona_todas_vagas(opcao);
            break;
        case 4:
            alterar();
            break;
        case 5:
            imprime_bd();
            break;
        default: std::cout << "Erro. Fechando programa "; break;
        }

    } while (opcao != 0);
    return 0;
}