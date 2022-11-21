#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include <time.h>

struct PatientInfo {
    char nome[100];
    char cpf[12];
    char data_nascimento[11];
    int idade;
    char telefone[14];
    char data_diagnostico[11];
    char endereco[100];
    char bairro[50];
    char cidade[50];
    char estado[50];
    char cep[13];
    char email[100];
    int possui_comorbidades;
    char comorbidades[200];
};

void show_patient_info(struct PatientInfo info) {
    printf("Nome: %s\n", info.nome);
    printf("Cpf: %s\n", info.cpf);
    printf("Data de Nascimento: %s\n", info.data_nascimento);
    printf("Telefone: %s\n", info.telefone);
    printf("Data do Diagnostico: %s\n", info.data_diagnostico);
    if(info.possui_comorbidades) {
        printf("Comorbidade: Sim\n");
        printf("\t%s\n", info.comorbidades);
    } else {
        printf("Comorbidade: Não\n");
    }
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

int calculate_age(char* date) {
    return 1;
}

void save_to_file(struct PatientInfo patient_info){
    FILE *output_file = fopen ("patients.dat", "a");

    if(output_file == NULL) {
        printf("NÃO FOI POSSÍVEL LER O ARQUIVO DE DADOS!!!");
        return;
    }

    fwrite(&patient_info, sizeof(struct PatientInfo), 1, output_file);
    fclose(output_file);
}

void save_to_file_2(struct PatientInfo patient_info){
    FILE *output_file = fopen ("patients.dat", "a");

    if(output_file == NULL) {
        printf("NÃO FOI POSSÍVEL LER O ARQUIVO DE DADOS!!!");
        return;
    }

    fwrite(&patient_info, sizeof(struct PatientInfo), 1, output_file);
    fclose(output_file);
}


void read_chars(char* message, char* output, int output_size) {
    do {
        printf("%s: ", message);
        // Usando fgets ao invés do scanf para ler espaços
        fgets(output, output_size, stdin);

        // Procurando char de nova linha para remoção
        char *ptr = strchr(output, '\n');
        if (ptr){
            // Se \n for achado fa a substituição pelo fim de linha
            *ptr  = '\0';
        }
        fflush(stdin);
    } while (strlen(output) == 0);
}

void ask_for_characters(char* message, char* output, int output_size) {
    int is_correct = 0;

    while(is_correct == 0) {
        is_correct = 1;
        read_chars(message, output, output_size);
        for(int idx = 0; idx < strlen(output); idx++) {
            if(!isalpha(output[idx]) && !isspace(output[idx])) {
                is_correct = 0;
            }
        }

        if(is_correct == 0) {
            printf("ERRO: Campo só pode conter letras. Digite novamente...\n");
        }
    }
}

void ask_for_numbers(char* message, char* output, int output_size) {
    int is_correct = 0;

    while(is_correct == 0) {
        is_correct = 1;
        read_chars(message, output, output_size);
        for(int idx = 0; idx < strlen(output); idx++) {
            if(!isdigit(output[idx])) {
                is_correct = 0;
            }
        }

        if(is_correct == 0) {
            printf("ERRO: Campo só pode conter números e sem espaço. Digite novamente...\n");
        }
    }
}

time_t ask_for_date(char* message, char* output) {
    time_t birthdate;

    struct tm tm = {0};

    int is_correct = 0;

    while(is_correct == 0) {
        is_correct = 1;
        read_chars(message, output, 11);

        char* s = strptime(output, "%d/%m/%Y", &tm);

        if(s == NULL) {
            printf("ERRO: Data inválida. Digite novamente no formato DD/MM/AAAA (ex. 10/11/2022)...\n");
            is_correct = 0;
        } else {
            time_t birthdate = mktime(&tm);
            printf("%f", birthdate);
        }
    }

    return birthdate;
}

struct PatientInfo ask_patient_info(){

    struct PatientInfo info;

    //ask_for_characters("Digite o nome", info.nome, 100);
    //ask_for_numbers("Digite o CPF", info.cpf, 12);
    time_t birthdate = ask_for_date("Digite a data de nascimento (DD/MM/AAAA)", info.data_nascimento);
    time_t today = time(NULL);
    printf("%d\n", difftime(birthdate, today);
    ask_for_numbers("Digite o telefone", info.telefone, 14);
    ask_for_date("Digite a data de diagnóstico (DD/MM/AAAA)", info.data_diagnostico);
    read_chars("Digite o endereço", info.endereco, 100);
    read_chars("Digite o bairro", info.bairro, 50);
    ask_for_characters("Digite a cidade", info.cidade, 50);
    ask_for_characters("Digite o estado", info.estado, 50);
    ask_for_numbers("CEP", info.cep, 13);
    read_chars("Digite o email", info.email, 100);

    char possui_comorbidade = '0';

    while(possui_comorbidade != 'S' && possui_comorbidade != 'N') {
        printf("Paciente possui alguma comorbidade (S - Sim N - Não): ");
        possui_comorbidade = getchar();
    }

    if (possui_comorbidade != 'N') {
        info.possui_comorbidades = 1;
        read_chars("Quais comorbidades o paciente possui", info.comorbidades, 200);
    } else {
        info.possui_comorbidades = 0;
    }


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

int main() {
    //while(login() == 0){}
    struct PatientInfo info = ask_patient_info();
    show_patient_info(info);
    //save_to_file(info);
    //get_patient_info();
}






