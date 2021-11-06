#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <locale.h>

int cod = 0; // variavel que guarda codigo (pegar ultimo codigo do bd)

//funcao que valida int
template<typename t>
void valida_input(t&input, const std::string msg)
{
    //impede casos de cin.fail (so por precaucao):
        std::cout << msg;
        std::cin >> input;
        while (std::cin.fail())
        {
            std::cout<<"\n>> Erro de entrada, tente novamente.\n";
            std::cin.clear();
            std::cin.ignore(9999, '\n');
            std::cout << msg;
            std::cin >> input;
        }           
}

//funcao do menu de opcoes (impressao e entrada)
void menu_de_opcoes(int& opcao_menu)
{
    std::cout<<"\nMenu de opcoes\n\n";
    std::cout<<"1 - Simular uma entrada\n";
    std::cout<<"2 - Simular uma saida\n";
    std::cout<<"3 - Apagar tudo (inclui pagamentos)\n";
    std::cout<<"0 - Sair do programa\n";
    //validacao de entrada do menu:
    do{
        valida_input(opcao_menu, "\nDigite a opcao: ");
        if (opcao_menu < 0 || opcao_menu > 3) std::cout<<"\n>>Insira apenas valores existentes no menu!\n";
    } while (opcao_menu < 0 || opcao_menu > 3);
    

}


void entrada()
{
    cod = cod+1;
   // data e hora baseadas nas config. locais
   time_t agora = time(0);
   // converte para string
   char* hora_entrada = ctime(&agora);
   std::cout << "Codigo do ticket simulado: " << cod << std::endl;
   std::cout << "Data e hora de entrada: " << hora_entrada << std::endl;
}

void saida()
{
    // data e hora baseadas nas config. locais
    time_t agora = time(0);
    // converte para string
    char* hora_saida = ctime(&agora);
    int cod_saida;
    valida_input(cod_saida, "Codigo do ticket: ");
        //pegar o codigo do bd
        /* */
        //checar se a saida foi liberada pelo sistema (no momento vo simular isso)
        int resposta;
        do{
            valida_input(resposta, "A saida do ticket foi liberada?(1=s/2=n)");
            if (resposta < 1 || resposta > 2) std::cout<<"\n>>Insira apenas 1 para 's' ou 2 para 'n'!\n";
        } while (resposta < 1 || resposta > 2);

        switch (resposta)
        {
            case 1: //'S' - saida liberada
                //escrever  cod ticket e hora de entrada 
                std::cout << "Data e hora de saida: " << hora_saida << std::endl;
                //envia pro bd
                break;

            case 2: //'N' - saida negada
                std::cout << "O pagamento da taxa de estacionamento nao foi realizado! " << std::endl;
            break;
        }


}

int main()
{
    int opcao;
    
    
    std::cout<<"Opcao digitada: "<<opcao; 
    do
    {
        //imprime menu
        menu_de_opcoes(opcao);
        
        switch(opcao)
        {
            case 1:
                entrada();                 
                break; 
            case 2:
                saida();                 
                break;
            case 3: 
                break;
            default: std::cout<<"Erro. Fechando programa "; break;
        }
        
    } while(opcao!=0);
    return 0;
}