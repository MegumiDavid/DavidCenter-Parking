#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <locale.h>

//matriz que contem as vagas
int andar1[4][15];
int andar2[4][15];
int andar3[4][15];
int andar4[4][15];
int andar5[4][15];

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



int main()
{
    int opcao, n, n_procurar,x, conta=0;
    
    
    std::cout<<"Opcao digitada: "<<opcao; 
    do
    {
        //imprime menu
        menu_de_opcoes(opcao);
        
        switch(opcao)
        {
            case 1:                 
                break; 
            case 2:                 
                break;
            case 3: 
                break;
            default: std::cout<<"Erro. Fechando programa "; break;
        }
        
    } while(opcao!=0);
    return 0;
}