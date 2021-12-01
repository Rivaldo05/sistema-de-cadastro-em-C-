#include <stdio.h> //  conjuto de funções printF, scanf...
#include <stdlib.h> // Emulador do prompt do SI... System(cls)..
#include <conio.h> // getch.. mudar cor do texto, etc
#include <locale.h> //acentuação de caracteres
#include <time.h> // manipula tempo
#include <String.h>
#include<stdbool.h>

 

// funções necessarias :
/*
    login - okay
    cadastro - OKAY
    salvar dados - OKAY
    exibir dados - OKAY
    pesquisar dados - okay
    Comobirdades - okay
*/

typedef struct Ano_Dia_Mes ano_nascimento; // defino o nome da struct e a referencia
// defino os dados da struct 
struct Ano_Dia_Mes {
    int dia;
    int mes;
    int ano;
    
};

typedef struct  hora_ano Hora_Ano;
struct hora_ano
{
    int hora;
    int min;
    int segundos;
    int ano;
    int mes;

};

typedef struct endereco dados_endereco;
struct endereco
{
    char endereco[50];
    char bairro[50];
    int num_casa;
    int cep;
    char cidade[30];
    char estado[10];
};

typedef struct Paciente_ficha paciente_ficha;// Cria uma STRUCT para armazenar os dados de uma pessoa
struct Paciente_ficha {
        char Nome[100];
        char cpf[12];
        ano_nascimento niver;
        char email[100];
        dados_endereco endereco;
        Hora_Ano hora_atendimento;
        char comorbidades[250];
    };


char loginSenha[] = "654321";
char loginUsuario[] = "SECRETARIA";

bool login_temp = false;

int main()
{   
    setlocale(LC_ALL, "Portuguese"); // seta o portugues como escrita
    login();

    int op;
    if (login_temp == true)
    {
        do
        {
            menu();
            printf("Sua escolha: ");
            

            scanf("%d", &op);
            switch (op)
            {
                case 1:
                    inputData();
                    break;
                case 2:
                    listarDados();
                    break;
                
                case 3:
                    listarGrupoRicos();
                    break;
                
                case 4:
                    pesquisar();
                    break;

                case 5:
                    printf("Encerrando programa!...");
                    login_temp = false;
                    getch();
                    break;
                
                default:
                    printf("Opcao invalida");

                    getch();
                    break;
            }
            
        } while (op !=5);
    }
    
return 0;
}


// FUNÇÕES 

void cabecalho(){
    system("cls");
    printf("------------------------------------");
    printf("\n----------Secretaria da Saude da cidade----------\n");
    printf("------------------------------------\n");
   
}

void login(){
    
    char usuario[20];
    char senha[10];
    while (login_temp != true)
    {
        cabecalho();
        printf("Senha : %s  Usuario: %s \n", loginSenha, loginUsuario);

        fflush(stdin);
        printf("Informe o usuario: ");
        gets(usuario); 
        strupr(usuario);// SALVA TUDO EM MAIUSCULO
        
        fflush(stdin);
        printf("Informe a senha: ");
        gets(senha);
        if (strcmp(usuario, loginUsuario) == 0 && strcmp(senha, loginSenha) == 0)
        {
            login_temp = true;
            
        }else{
            login_temp = false;
            printf("Usuario ou senha incorreto...");
            getch();
        }
        
    }    
}

void menu(){
    cabecalho();
    printf("1 - inserir dados \n");
    printf("2 - Listar cadastro geral \n");
    printf("3 - Listar grupo de risco \n");
    printf("4 - Pesquisar paciente \n");
    printf("5 - Sair \n");

}

void inputData(){
    FILE * arquivo;
    paciente_ficha pacienteficha;

    /// padrao do c, obrigado a usar isso por parte da biblioteca TIME//
    struct  tm * data_hora_atual; 

    time_t segundos; // cria uma variavel que consegue guardar os segundos

    time(&segundos); //  obtendo o tempo em segundos
    data_hora_atual = localtime(&segundos); // para fazer as conversões de tempo local
    /////////////////////////

    
    // abre o arquivo  com append (adicona texto ao que já existe)
    //arquivo = fopen("Atendimentos_geral.txt", "ab");
    if (arquivo == NULL)
    {
        printf("ERRO AO TENTAR ABRIR O ARQUIVO"); // erro caso o arquivo não seja criado / exista

    }else{
        do
        {
            cabecalho();
            fflush(stdin);
            printf("Digite o nome:");
            gets(pacienteficha.Nome);

            fflush(stdin); // limpa o teclado
            printf("Informe o endereco:");
            gets(pacienteficha.endereco.endereco); //

            fflush(stdin);
            printf("Informe o bairro:");
            gets(pacienteficha.endereco.bairro); // não recomendavel, mas não aprendi a usar o fgets ainda. em resumo, é semelhante ao scanf. o problema é que não existe um limite para oq ela vai pegar

            fflush(stdin);
            printf("Informe o número da casa:");
            scanf("%d",&pacienteficha.endereco.num_casa);

            fflush(stdin);
            printf("Informe o Cep : ");
            scanf("%d", &pacienteficha.endereco.cep); // leitura de dados via teclado

            fflush(stdin);
            printf("Informe a Cidade : ");
            gets(pacienteficha.endereco.cidade);

            fflush(stdin);
            printf("Informe o Estado : ");
            gets(pacienteficha.endereco.estado);

            fflush(stdin); // limpa teclado
            printf("Informe a data de nascimento:");

            printf("Dia:");
            scanf("%d", &pacienteficha.niver.dia);
            fflush(stdin); // limpa teclado,

            printf("Mes:");
            scanf("%d", &pacienteficha.niver.mes);
            fflush(stdin); // limpa teclado

            printf("Ano:");
            scanf("%d", &pacienteficha.niver.ano);

            fflush(stdin);
            printf("Informe o E-Mail : ");
            gets(pacienteficha.email);

            fflush(stdin);
            printf("Comorbidades: ");
            gets(pacienteficha.comorbidades);

            pacienteficha.hora_atendimento.hora = data_hora_atual->tm_hour;
            pacienteficha.hora_atendimento.min = data_hora_atual->tm_min;
            pacienteficha.hora_atendimento.segundos = data_hora_atual->tm_sec;
            pacienteficha.hora_atendimento.ano = data_hora_atual->tm_year + 1900;
            pacienteficha.hora_atendimento.mes = data_hora_atual->tm_mon+1;
            

            // salva no arquivo
            if ((pacienteficha.hora_atendimento.ano) - pacienteficha.niver.ano >= 65)
            {
               arquivo = fopen("Atendimentos_Grupo_Risco.txt", "ab");
               fwrite(&pacienteficha, sizeof(paciente_ficha), 1,arquivo);
               fclose(arquivo);

            }

            arquivo = fopen("Atendimentos_Geral.txt", "ab");
            
            fwrite(&pacienteficha, sizeof(paciente_ficha), 1,arquivo); // escreve oq tem em paciente ficha no arquivo .txt... tudo oq esta dentro dos parenteses são parametros da propia função. Link : https://terminalroot.com.br/2014/10/exemplos-de-funcoes-fread-fwrite-remove.html
            fclose(arquivo);
            printf("deseja continuar(s/n)?");

        } while (getche() =='s');
        
        
    }
    
}


// listar dados, mais pra frente seria bom uma única função para exibir os dados e passar o arquivo txt como entrada da função
void listarDados(){

    FILE * arquivo;
    paciente_ficha pacienteficha;

    cabecalho();
    arquivo = fopen("Atendimentos_Geral.txt", "rb");
    if (arquivo == NULL)
    {
        printf("ERRO AO TENTAR ABRIR O ARQUIVO");

    }else{
        while (fread(&pacienteficha, sizeof(paciente_ficha),1, arquivo) == 1)
        {
            printf("nome : %s \n", pacienteficha.Nome);

            printf("rua : %s ", pacienteficha.endereco.endereco);

            printf("Numero da casa: %d \n", pacienteficha.endereco.num_casa);

            printf("Bairro : %s \nCep: %d \n",pacienteficha.endereco.bairro, pacienteficha.endereco.cep);

            printf("Cidade : %s Estado : %s \n", pacienteficha.endereco.cidade, pacienteficha.endereco.estado);

            printf("E-Mail: %s \n", pacienteficha.email);

            printf("aniversario : %d / %d / %d \n", pacienteficha.niver.dia, pacienteficha.niver.mes, pacienteficha.niver.ano);

            printf("Idade do paciente : %d \n", (pacienteficha.hora_atendimento.ano)- pacienteficha.niver.ano );

            printf("Comorbidades : %s \n", pacienteficha.comorbidades);

            printf("Hora do atendimento : %d : %d : %d de %d / %d", pacienteficha.hora_atendimento.hora, pacienteficha.hora_atendimento.min, pacienteficha.hora_atendimento.segundos, pacienteficha.hora_atendimento.mes, pacienteficha.hora_atendimento.ano);

            printf("\n----------------------------------------\n");
        }
        
    }
    fclose(arquivo);
    printf("Pressione qualquer tecla para continuar...");
    getch();
}

void listarGrupoRicos(){

    FILE * arquivo;
    paciente_ficha pacienteficha;

    cabecalho();
    arquivo = fopen("Atendimentos_Grupo_Risco.txt", "rb");
    if (arquivo == NULL)
    {
        printf("ERRO AO TENTAR ABRIR O ARQUIVO");

    }else{
        while (fread(&pacienteficha, sizeof(paciente_ficha),1, arquivo) == 1)
        {
            printf("nome : %s \n", pacienteficha.Nome);

            printf("rua : %s ", pacienteficha.endereco.endereco);

            printf("Numero da casa: %d \n", pacienteficha.endereco.num_casa);

            printf("Bairro : %s \nCep: %d \n",pacienteficha.endereco.bairro, pacienteficha.endereco.cep);

            printf("Cidade : %s Estado : %s \n", pacienteficha.endereco.cidade, pacienteficha.endereco.estado);

            printf("E-Mail: %s \n", pacienteficha.email);

            printf("aniversario : %d / %d / %d \n", pacienteficha.niver.dia, pacienteficha.niver.mes, pacienteficha.niver.ano);

            printf("Idade do paciente : %d \n", (pacienteficha.hora_atendimento.ano)- pacienteficha.niver.ano );

            printf("Comorbidades : %s \n", pacienteficha.comorbidades);

            printf("Hora do atendimento : %d : %d : %d de %d / %d", pacienteficha.hora_atendimento.hora, pacienteficha.hora_atendimento.min, pacienteficha.hora_atendimento.segundos, pacienteficha.hora_atendimento.mes, pacienteficha.hora_atendimento.ano);

            printf("\n----------------------------------------\n");
        }
        
    }
    fclose(arquivo);
    printf("Pressione qualquer tecla para continuar...");
    getch();
}

void pesquisar(){
    FILE * arquivo;
    paciente_ficha pacienteficha;
    char pesquisaNome[50];

    cabecalho();
    arquivo = fopen("Atendimentos_Geral.txt", "rb");
    if (arquivo == NULL)
    {
        printf("ERRO AO ABRIR O ARQUIVO");

    }else{
        fflush(stdin);
        printf("Digite o nome do paciente: \n");
        gets(pesquisaNome);

        while (fread(&pacienteficha, sizeof(paciente_ficha),1, arquivo) == 1)
        {
            if (strcmp(pesquisaNome, pacienteficha.Nome) == 0)
            {
                printf("nome : %s \n", pacienteficha.Nome);

                printf("rua : %s ", pacienteficha.endereco.endereco);

                printf("Numero da casa: %d \n", pacienteficha.endereco.num_casa);

                printf("Bairro : %s \nCep: %d \n",pacienteficha.endereco.bairro, pacienteficha.endereco.cep);

                printf("Cidade : %s Estado : %s \n", pacienteficha.endereco.cidade, pacienteficha.endereco.estado);

                printf("E-Mail: %s \n", pacienteficha.email);

                printf("aniversario : %d / %d / %d \n", pacienteficha.niver.dia, pacienteficha.niver.mes, pacienteficha.niver.ano);

                printf("Idade do paciente : %d \n", (pacienteficha.hora_atendimento.ano)- pacienteficha.niver.ano );

                printf("Comorbidades : %s \n", pacienteficha.comorbidades);

                printf("Hora do atendimento : %d : %d : %d de %d / %d", pacienteficha.hora_atendimento.hora, pacienteficha.hora_atendimento.min, pacienteficha.hora_atendimento.segundos, pacienteficha.hora_atendimento.mes, pacienteficha.hora_atendimento.ano);

                printf("\n----------------------------------------\n");
            }
            
        }
        if (strcmp(pesquisaNome, pacienteficha.Nome) > 0 || strcmp(pesquisaNome, pacienteficha.Nome) < 0)
            {
                printf("Paciebte nao encontrado \n");
            }
        
    }
    fclose(arquivo);
    printf("Pressione qualquer tecla para continuar...");
    getch();
}