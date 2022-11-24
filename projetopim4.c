#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include <time.h>

struct PatientInfo {
    char nome[100];
    char cpf[12];
    char data_nascimento[11];
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

/*
struct tm
  int tm_mday;          Dia
  int tm_mon;           Mês
  int tm_year;          Ano
*/
int calculate_age(char* birthdate) {
    // Converte a data
    struct tm birthdate_tm = {0};
    strptime(birthdate, "%d/%m/%Y", &birthdate_tm);

    // Pega a data atual
    time_t now;
    time(&now);
    struct tm* today = localtime(&now);
    
    // Calcula a idade
    int age = today->tm_year - birthdate_tm.tm_year;

    // Verifica se o dia do ano é menor que o dia do nascimento
    if (today->tm_yday < birthdate_tm.tm_yday) {
        // Retira um ano pois não fez aniversário ainda
        age -= 1;
    }
    
    return age;
}

void show_patient_info(struct PatientInfo info) {
    printf("Nome: %s\n", info.nome);
    printf("Cpf: %s\n", info.cpf);
    printf("Data de Nascimento: %s\n", info.data_nascimento);
    printf("Idade: %d\n", calculate_age(info.data_nascimento));
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
    FILE *input_file = fopen("dados_pacientes.dat", "r");

    if(input_file == NULL) {
        printf("NÃO FOI POSSÍVEL LER O ARQUIVO DE DADOS!!!\n");
        return;
    }

    while(fread(&info, sizeof(struct PatientInfo), 1, input_file)) {
        printf("---------------------------------------\n");
        show_patient_info(info);
    }
}

void save_to_file(struct PatientInfo patient_info){
    FILE *output_file = fopen ("dados_pacientes.dat", "a");

    if(output_file == NULL) {
        printf("NÃO FOI POSSÍVEL ABRIR O ARQUIVO DE DADOS!!!\n");
        return;
    }

    // Salva em binário para facilitar a leitura pelo programa
    fwrite(&patient_info, sizeof(struct PatientInfo), 1, output_file);
    fclose(output_file);
}

void save_to_send(char* cep, int age){
    FILE *output_file = fopen ("pacientes_grupos_risco.txt", "a");

    if(output_file == NULL) {
        printf("NÃO FOI POSSÍVEL ABRIR O ARQUIVO DE DADOS!!!\n");
        return;
    }

    // Salvando como texto
    fprintf(output_file, "%s %d\n",cep, age);
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
        // Pra limpar sujeira
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

void ask_for_date(char* message, char* output) {
    struct tm birthdate = {0};

    int is_correct = 0;

    while(is_correct == 0) {
        is_correct = 1;
        read_chars(message, output, 11);

        char* s = strptime(output, "%d/%m/%Y", &birthdate);

        if(s == NULL) {
            printf("ERRO: Data inválida. Digite novamente no formato DD/MM/AAAA (ex. 10/11/2022)...\n");
            is_correct = 0;
        }
    }
}

void ask_patient_info(){

    struct PatientInfo info;

    ask_for_characters("Digite o nome", info.nome, 100);
    ask_for_numbers("Digite o CPF", info.cpf, 12);
    ask_for_date("Digite a data de nascimento (DD/MM/AAAA)", info.data_nascimento);

    ask_for_numbers("Digite o telefone", info.telefone, 14);
    ask_for_date("Digite a data de diagnóstico (DD/MM/AAAA)", info.data_diagnostico);
    read_chars("Digite o endereço", info.endereco, 100);
    read_chars("Digite o bairro", info.bairro, 50);
    ask_for_characters("Digite a cidade", info.cidade, 50);
    ask_for_characters("Digite o estado", info.estado, 50);
    ask_for_numbers("Digite o CEP", info.cep, 13);
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

    save_to_file(info);

    int age = calculate_age(info.data_nascimento);
    if (age >= 65 && info.possui_comorbidades) {
        printf("---------------------------------------\n");
        printf("Paciente em grupo de risco\n");
        printf("Salvando dados para envio a central de secretária de saúde\n");
        save_to_send(info.cep, age);
    }
}


int login(){

    char login[20];

    printf("Digite o login: ");
    scanf("%s",login);

    char senha[15];

    printf("Digite a senha: ");
    scanf("%s", senha);

    printf("---------------------------------------\n");
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
    printf("======================================================\n");
    printf("\tSISTEMA DE CADASTRO DE PACIENTES COM COVID\t\n");
    printf("======================================================\n");
    while(login() == 0){}
    
    char opt;
    do
    {
        // Pra limpar sujeira
        fflush(stdin);
        printf("======================================================\n");
        printf("1 - Cadastrar Paciente\n");
        printf("2 - Lista de Pacientes\n");
        printf("3 - Sair\n");
        printf("Opção: ");
        opt = getchar();
        printf("======================================================\n");

        if(opt == '1'){
            ask_patient_info();
        } else if (opt == '2'){
            get_patient_info();
        }
        else if (opt != '3'){
            printf("Opção %c não reconhecida!\n", opt);
        }
    } while (opt != '3');

    return 0;
}






