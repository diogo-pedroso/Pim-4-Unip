#include<stdio.h>
#include<string.h>

struct PatientInfo {
    char nome[20];
    char cpf[11];
    char nascimento[10];
    char telefone[13];
    char diagnostico[12];
    char comorbidades[40];
    char endereco[15];
    char bairro[15];
    char cidade[15];
    char estado[15];
    char cep[12];
    char email[20];
};

void show_patient_info(struct PatientInfo info) {
    printf("Nome: %s\n", info.nome);
    printf("Cpf: %s\n", info.cpf);
    printf("Data de Nascimento: %s\n", info.nascimento);
    printf("Telefone: %s\n", info.telefone);
    printf("Data do Diagnostico: %s\n", info.diagnostico);
    printf("Comorbidade: %s\n", info.comorbidades);
    printf("Endereço: %s; %s; %s; %s; %s\n", info.endereco, info.bairro, info.cidade, info.estado, info.cep);
    printf("Email: %s\n", info.email);
}

void get_patient_info(){
    struct PatientInfo info;
    FILE *input_file = fopen("patients.dat", "r");

    if(input_file == NULL) {
        printf("NÃO FOI POSSÍVEL LER O ARQUIVO DE DADOS!!!");
        return;
    }

    while(fread(&info, sizeof(struct PatientInfo), 1, input_file)) {
        show_patient_info(info);
    }
}

void save_to_file(struct PatientInfo patient_info){
    FILE *output_file = fopen ("patients.dat", "a");

    if(input_file == NULL) {
        printf("NÃO FOI POSSÍVEL LER O ARQUIVO DE DADOS!!!");
        return;
    }

    fwrite(&patient_info, sizeof(struct PatientInfo), 1, output_file);
    fclose(output_file);
}

struct PatientInfo ask_patient_info(){

    struct PatientInfo info;

    printf("Digite o nome: ");
    scanf("%s", info.nome);

    printf("Insira o cpf: ");
    scanf("%s", info.cpf);

    printf("Digite a data de nascimento: ");
    scanf("%s", info.nascimento);

    printf("Digite o telefone: ");
    scanf("%s", info.telefone);

    printf("Digite a data do diagnostico: ");
    scanf("%s", info.diagnostico);

    printf("Insira qual comorbidade do paciente: ");
    scanf("%s", info.comorbidades);

    printf("Digite o número da casa: ");
    scanf("%s", info.endereco);

    printf("Digite o bairro: ");
    scanf("%s", info.bairro);

    printf("Digite a cidade: ");
    scanf("%s", info.cidade);

    printf("Digite o estado: ");
    scanf("%s", info.estado);

    printf("Digite o CEP: ");
    scanf("%s", info.cep);

    printf("Digite o email: ");
    scanf("%s", info.email);

    return info;
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
    struct PatientInfo info = ask_patient_info();
    save_to_file(info);
    get_patient_info();
}