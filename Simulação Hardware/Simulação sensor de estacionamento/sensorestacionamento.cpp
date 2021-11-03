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
    std::cout<<"1 - Inserir vagas aleatorias\n";
    std::cout<<"2 - Inserir '0' em todas as vagas\n";
    std::cout<<"3 - Inserir '1' em todas as vagas\n";
    std::cout<<"4 - Alterar vagas existentes\n";
    std::cout<<"5 - Imprimir mapa de vagas\n";
    std::cout<<"0 - Sair do programa\n";
    //validacao de entrada do menu:
    do{
        valida_input(opcao_menu, "\nDigite a opcao: ");
        if (opcao_menu < 0 || opcao_menu > 5) std::cout<<"\n>>Insira apenas valores existentes no menu!\n";
    } while (opcao_menu < 0 || opcao_menu > 5);
    

}


void insere_aleatorio()
{ 
    int x, i, j;
    srand((unsigned)time(0));       //seed do numero gerado aleatoreamente 
    
    for (x=0; x<5; x++)
    {
        switch (x+1)
        {
            case 1:
                for (i=0; i<4; i++)
                {
                    for (j=0; j<15; j++)
                    {
                        andar1[i][j] = rand()%2;
                    }
                }
                break;
            case 2:
                for (i=0; i<4; i++)
                {
                    for (j=0; j<15; j++)
                    {
                        andar2[i][j] = rand()%2;
                    }
                }
                break;
            case 3:
                for (i=0; i<4; i++)
                {
                    for (j=0; j<15; j++)
                    {
                        andar3[i][j] = rand()%2;
                    }
                }
                break;
            case 4:
                for (i=0; i<4; i++)
                {
                    for (j=0; j<15; j++)
                    {
                        andar4[i][j] = rand()%2;
                    }
                }
                break;
            case 5:
                for (i=0; i<4; i++)
                {
                    for (j=0; j<15; j++)
                    {
                        andar5[i][j] = rand()%2;
                    }
                }
                break;
        }
        
    }
    std::cout<<"\n>>Vagas alteradas com sucesso!\n";
}

void insere_zero_ou_um(int n)
{
    int x, i, j;

    for (x=0; x<5; x++)
    {
        switch (x+1)
        {
            case 1:
                for (i=0; i<4; i++)
                {
                    for (j=0; j<15; j++)
                    {
                        andar1[i][j] = n;
                    }
                }
                break;
            case 2:
                for (i=0; i<4; i++)
                {
                    for (j=0; j<15; j++)
                    {
                        andar2[i][j] = n;
                    }
                }
                break;
            case 3:
                for (i=0; i<4; i++)
                {
                    for (j=0; j<15; j++)
                    {
                        andar3[i][j] = n;
                    }
                }
                break;
            case 4:
                for (i=0; i<4; i++)
                {
                    for (j=0; j<15; j++)
                    {
                        andar4[i][j] = n;
                    }
                }
                break;
            case 5:
                for (i=0; i<4; i++)
                {
                    for (j=0; j<15; j++)
                    {
                        andar5[i][j] = n;
                    }
                }
                break;
        }
        
    }
    std::cout<<"\n>>Vagas alteradas com sucesso!\n";
}

void imprime()
{
    char a;
    int x,i,j;
    srand((unsigned)time(0));       //seed do numero gerado aleatoreamente 
    
    for (x=0; x<5; x++)
    {
        switch (x+1)
        {
            case 1:
                std::cout << "Andar 1: \n";
                for(i = 0; i < 4; i++)
                {
                    if (i == 0) a = 65;
                    if (i == 1) a = 66;
                    if (i == 2) a = 67;
                    if (i == 3) a = 68;
                    std::cout << "\n" << a << ": \n";
                    for (j = 0; j < 15; j++)
                    {
                        std::cout << std::setw(5) << andar1[i][j];
                    }
                }
                break;
            case 2:
                std::cout << "\n\nAndar 2: \n";
                for(i = 0; i < 4; i++)
                {
                    if (i == 0) a = 65;
                    if (i == 1) a = 66;
                    if (i == 2) a = 67;
                    if (i == 3) a = 68;
                    std::cout << "\n" << a << ": \n";
                    for (j = 0; j < 15; j++)
                    {
                        std::cout << std::setw(5) << andar2[i][j];
                    }
                }
                break;
            case 3:
                std::cout << "\n\nAndar 3: \n";
                for(i = 0; i < 4; i++)
                {
                    if (i == 0) a = 65;
                    if (i == 1) a = 66;
                    if (i == 2) a = 67;
                    if (i == 3) a = 68;
                    std::cout << "\n" << a << ": \n";
                    for (j = 0; j < 15; j++)
                    {
                        std::cout << std::setw(5) << andar3[i][j];
                    }
                }
                break;
            case 4:
                std::cout << "\n\nAndar 4: \n";
                for(i = 0; i < 4; i++)
                {
                    if (i == 0) a = 65;
                    if (i == 1) a = 66;
                    if (i == 2) a = 67;
                    if (i == 3) a = 68;
                    std::cout << "\n" << a << ": \n";
                    for (j = 0; j < 15; j++)
                    {
                        std::cout << std::setw(5) << andar4[i][j];
                    }
                }
                break;
            case 5:
                std::cout << "\n\nAndar 5: \n";
                for(i = 0; i < 4; i++)
                {
                    if (i == 0) a = 65;
                    if (i == 1) a = 66;
                    if (i == 2) a = 67;
                    if (i == 3) a = 68;
                    std::cout << "\n" << a << ": \n";
                    for (j = 0; j < 15; j++)
                    {
                        std::cout << std::setw(5) << andar5[i][j];
                    }
                }
                break;
        }
        
    }
    
}    


void alterar()
{
    int n_andar, vaga, blocon;
    char bloco;
    do
    {
        valida_input(n_andar, "Alterar vaga em qual andar? ");
        if (n_andar < 1 || n_andar > 5) std::cout<<"\n>>Insira apenas valores entre 1 e 5!\n";
    } while (n_andar < 1 || n_andar > 5);
    do
    {
        valida_input(bloco, "Alterar vaga em qual bloco? ");
        bloco = toupper(bloco);
        if (bloco<'A' || bloco>'D') std::cout<<"\n>>Insira apenas letras de 'A' a 'D'!\n";
        switch (bloco)
        {
            case 65:
                blocon = 0;
                break;
            case 66:
                blocon = 1;
                break;
            case 67:
                blocon = 2;
                break;
            case 68:
                blocon = 3;
                break;
        }

    } while (bloco<'A' || bloco>'D');
    {
        valida_input(vaga, "Alterar qual vaga (1-15)? ");
        if (vaga<1 || vaga>15) std::cout<<"\n>>Insira apenas letras de 'A' a 'D'!\n";
    } while (vaga<1 || vaga>15);
    vaga--;
    
    switch (n_andar)
    {
        
        case 1:
            if (andar1[blocon][vaga]==0) andar1[blocon][vaga]=1;
            else andar1[blocon][vaga]=0;
            break;  
        case 2:
            if (andar2[blocon][vaga]==0) andar2[blocon][vaga]=1;
            else andar2[blocon][vaga]=0;
            break;
        case 3:
            if (andar3[blocon][vaga]==0) andar3[blocon][vaga]=1;
            else andar3[blocon][vaga]=0;
            break;
        case 4:
            if (andar4[blocon][vaga]==0) andar4[blocon][vaga]=1;
            else andar4[blocon][vaga]=0;
            break;
        case 5:
            if (andar5[blocon][vaga]==0) andar5[blocon][vaga]=1; 
            else andar5[blocon][vaga]=0;
            break;
    }

    std::cout<<"\n>>Vaga alterada com sucesso!\n";
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
                insere_aleatorio();
                break; 
            case 2:                 
                insere_zero_ou_um(0);
                break;
            case 3: 
                insere_zero_ou_um(1);
                break;
            case 4: 
                alterar();
                break;
            case 5:
                imprime();
                break;
            default: std::cout<<"Erro. Fechando programa "; break;
        }
        
    } while(opcao!=0);
    return 0;
}