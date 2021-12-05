#include <mysql.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <locale.h>

//declarando variaveis para acesso do bd
char* usr = (char*)"****"; //substituir por info do bd
char* pass = (char*)"*******";
char* db = (char*)"DavidCenter";

int qstado;

MYSQL mysql, * conn;
MYSQL_RES result;
MYSQL_ROW linha;
//estado do query.
int qstate;

//conecta com o bd e imprime todas as informacoes de ticket, sem considerar pagamentos, depois fecha a conexao
void imprime_bd()
{
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", usr, pass, db, 3306, NULL, 0);

    if (conn) {
        puts("Conexao com o Banco de Dados bem sucedida!");

        std::string query = "SELECT * FROM tickets";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (linha = mysql_fetch_row(res))
            {
                printf("CODIGO_TICKET: %s, HORA_ENTRADA: %s, HORA_SAIDA: %s, STATUS_SAIDA: %s\n", linha[0], linha[1], linha[2], linha[3]);
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

//conecta com o bd e roda um comando, depois fecha a conexao
int rodacomando(std::string comando)
{
    mysql_init(&mysql);
    std::string instrucao = comando;
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

//conecta com o bd e checa se um codigo existe, depois fecha a conexao
int checa_cod(std::string cod_compara)
{
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", usr, pass, db, 3306, NULL, 0);

    if (conn) {
        puts("Conexao com o Banco de Dados bem sucedida!");

        std::string query = "SELECT * FROM tickets";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (linha = mysql_fetch_row(res))
            {
                if (linha[0] == cod_compara) return 0;
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
    return 1;
}

//conecta com o bd e checa o status da saida de um codigo, depois fecha a conexao
int checastatus(std::string cod)
{
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", usr, pass, db, 3306, NULL, 0);

    if (conn) {

        std::string query = "SELECT * FROM tickets WHERE CODIGO_TICKET = '" + cod + "';";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (linha = mysql_fetch_row(res))
            {
                if (strcmp(linha[3],"OK") == 0) return 0;
                else return 1;
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
    return 2;
}

//conecta com o bd e checa o status da saida de um codigo, depois fecha a conexao
int checadiff(std::string cod)
{
    int x;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", usr, pass, db, 3306, NULL, 0);

    if (conn) {

        std::string query = "select CalcDiff(HORA_ENTRADA, now()) from PAGAMENTOS, TICKETS where CODIGO_TICKET = '" + cod + "';"; 
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (linha = mysql_fetch_row(res))
            {
                sscanf(linha[0], "%d", &x);
                return x;
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
    std::cout << "1 - Simular uma entrada\n";
    std::cout << "2 - Simular uma saida\n";
    std::cout << "3 - Imprimir BD\n";
    std::cout << "4 - Apagar tickets (deixara pagamentos orfaos no bd)\n";
    std::cout << "5 - Reiniciar contador de codigo de ticket\n";
    std::cout << "6 - Apagar pagamentos (caso necessario)\n";
    std::cout << "0 - Sair do programa\n";
    //validacao de entrada do menu:
    do {
        valida_input(opcao_menu, "\nDigite a opcao: ");
        if (opcao_menu < 0 || opcao_menu > 6) std::cout << "\n>>Insira apenas valores existentes no menu!\n";
    } while (opcao_menu < 0 || opcao_menu > 6);

}

//simula uma saida
void saida()
{
    int checa, status;
    int cod_saida;
    valida_input(cod_saida, "Codigo do ticket: ");
    //checar se a saida foi liberada pelo sistema (no momento vou simular isso)
    checa = checa_cod(std::to_string(cod_saida));
    if (checa == 1) std::cout << "Codigo nao existe no Banco de Dados!";
    else
    {
        status = checastatus(std::to_string(cod_saida));

        switch (status)
        {
        case 0: // - saida liberada
            //escrever  cod ticket e hora de entrada 
            //insere_bd_saida(hora_saida, std::to_string(cod_saida));
            rodacomando("UPDATE tickets set hora_saida = now() WHERE CODIGO_TICKET = '" + std::to_string(cod_saida) + "';");
            break;
        case 1: // - saida negada
            if (checadiff(std::to_string(cod_saida)) <= 15)
                rodacomando("UPDATE tickets set hora_saida = now(), status_saida ='OK' WHERE CODIGO_TICKET = '" + std::to_string(cod_saida) + "';");
            else std::cout << "O pagamento da taxa de estacionamento nao foi realizado! " << std::endl;
            break;
        default:
            std::cout << "Erro ao checar status de saida! " << std::endl;
            break;
        }
    }
}


int main()
{
    int opcao;
    do
    {
        //imprime menu
        menu_de_opcoes(opcao);

        switch (opcao)
        {
        case 1:
            //insere_bd_entrada(hora_entrada, 'DENIED');
            rodacomando("insert into tickets (hora_entrada, status_saida) values (now(), 'DENIED'); ");
            break;
        case 2:
            saida();
            break;
        case 3:
            imprime_bd();
            break;
        case 4:
            rodacomando("DELETE FROM tickets;");
            break;
        case 5: 
            rodacomando("ALTER TABLE tickets AUTO_INCREMENT = 1;");
            break;
        case 6:
            rodacomando("DELETE FROM pagamentos; ");
            break;
        default: std::cout << "Fechando programa. "; break;
        }

    } while (opcao != 0);
    return 0;
}