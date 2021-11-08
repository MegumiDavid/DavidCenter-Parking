#include <mysql.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <iomanip>
#include <locale.h>

//declarando variaveis para acesso do bd
char* usr = (char*)"root";
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

        std::string query = "SELECT * FROM CLIENTES";
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

        std::string query = "SELECT * FROM CLIENTES";
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

//simula uma entrada
void entrada()
{
    // data e hora baseadas nas config. locais
    time_t agora = time(0);
    // converte para string
    std::string hora_entrada = ctime(&agora);
    //insere_bd_entrada(hora_entrada, "NEGADA");
    rodacomando("insert into clientes (hora_entrada, status_saida) values ('" + hora_entrada + "', 'NEGADA'); ");
}

//simula uma saida
void saida()
{
    int checa;
    // data e hora baseadas nas config. locais
    time_t agora = time(0);
    std::string hora_saida = ctime(&agora);
    int cod_saida;
    valida_input(cod_saida, "Codigo do ticket: ");
    //checar se a saida foi liberada pelo sistema (no momento vou simular isso)
    checa = checa_cod(std::to_string(cod_saida));
    if (checa == 1) std::cout << "Codigo nao existe no Banco de Dados!";
    else
    {
        int resposta;
        do {
            valida_input(resposta, "A saida do ticket foi liberada?(1=s/2=n)");
            if (resposta < 1 || resposta > 2) std::cout << "\n>>Insira apenas 1 para 's' ou 2 para 'n'!\n";
        } while (resposta < 1 || resposta > 2);

        switch (resposta)
        {
        case 1: //'S' - saida liberada
            //escrever  cod ticket e hora de entrada 
            //insere_bd_saida(hora_saida, "LIBERADA", std::to_string(cod_saida));
            rodacomando("UPDATE clientes set hora_saida = ' " + hora_saida + "', status_saida = 'LIBERADA' WHERE CODIGO_TICKET = '" + std::to_string(cod_saida) + "';");
            //envia pro bd
            break;

        case 2: //'N' - saida negada
            std::cout << "O pagamento da taxa de estacionamento nao foi realizado! " << std::endl;
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
            entrada();
            break;
        case 2:
            saida();
            break;
        case 3:
            imprime_bd();
            break;
        case 4:
            rodacomando("DELETE FROM clientes;");
            /*DELETE FROM clientes;
            ALTER TABLE clientes AUTO_INCREMENT = 1;*/
            break;
        case 5: 
            rodacomando("ALTER TABLE clientes AUTO_INCREMENT = 1;");
            break;
        case 6:
            rodacomando("DELETE FROM taxas; ");
            break;
        default: std::cout << "Fechando programa. "; break;
        }

    } while (opcao != 0);
    return 0;
}