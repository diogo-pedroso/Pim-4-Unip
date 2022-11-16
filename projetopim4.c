#include<stdio.h>
#include<string.h>

void get_patient_info(){

    char nome[20];

    printf("Digite o nome: ");
    scanf("%s", nome);

    char cpf[12];

    printf("Insira o cpf: ");
    scanf("%s", cpf);

    char nascimento[10];

    printf("Digite a data de nascimento: ");
    scanf("%s", nascimento);

    char telefone[13];

    printf("Digite o telefone: ");
    scanf("%s", telefone);

    char diagnostico[12];

    printf("Digite a data do diagnostico: ");
    scanf("%s", diagnostico);

    char comorbidades[40];

    printf("Insira qual comorbidade do paciente: ");
    scanf("%s", comorbidades);

    char rua[15];

    printf("Digite o número da casa: \n");
    scanf("%s", rua);

    char bairro[15];

    printf("Digite o bairro: ");
    scanf("%s", bairro);

    char cidade[15];

    printf("Digite a cidade: ");
    scanf("%s", cidade);

    char estado[15];

    printf("Digite o estado: ");
    scanf("%s", estado);

    char CEP[12];

    printf("Digite o CEP: ");
    scanf("%s", CEP);


    char Email[20];

    printf("Digite o Email: ");
    scanf("%s", Email);
}


int login(){

    char login[20];

    printf("Digite o login: ");
    scanf("%s",login);

    char senha[15];

    printf("Digite a senha: ");
    scanf("%s", senha);

    if(strcmp(login,"uns_covid") == 0){
        if(strcmp(senha,"123456789") == 0){
            printf("Acesso Liberado \n");
            return 1;
        } else {
            printf("Senha incorreta \n");

        }

    } else {
        printf("O login esta incorreto \n");

    }

    return 0;
}

int main(){
    while(login() == 0){}

}
