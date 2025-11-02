#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

typedef struct
{
    string nome;
    int votos;
} candidato;

candidato candidatos[MAX];
int quantidade_candidatos;
bool votar(string nome);
void imprimir_vencedor(void);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Digite: Plurality [candidato ...]\n");
        return 1;
    }

    quantidade_candidatos = argc - 1;
    if (quantidade_candidatos > MAX)
    {
        printf("O número máximo de candidatos é %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < quantidade_candidatos; i++)
    {
        candidatos[i].nome = argv[i + 1];
        candidatos[i].votos = 0;
    }
    int quantidade_votos = get_int("Número de votos: ");

    for (int i = 0; i < quantidade_votos; i++)
    {
        string nome = get_string("Voto: ");
        if (!votar(nome))
        {
            printf("Voto inválido.\n");
        }
    }

    imprimir_vencedor();
}

bool votar(string nome)
{
    for (int i = 0; i < quantidade_candidatos; i++)
    {
        if (strcmp(candidatos[i].nome, nome) == 0)
        {
            candidatos[i].votos++;
            return true;
        }
    }
    return false;
}

void imprimir_vencedor(void)
{
    int maximo_votos = 0;

    for (int i = 0; i < quantidade_candidatos; i++)
    {
        if (candidatos[i].votos > maximo_votos)
        {
            printf("%s\n", candidatos[i].nome);
        }
    }

    return;
}
