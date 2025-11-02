#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CANDIDATOS 9
#define MAX_ELEITORES 100

typedef struct
{
    string nome;
    int votos;
    bool eliminado;
}
candidato;

candidato candidatos[MAX_CANDIDATOS];

int preferencias[MAX_ELEITORES][MAX_CANDIDATOS];

int quantidade_eleitores;
int quantidade_candidatos;

bool votar(int eleitor, int rank, string nome);
void tabular(void);
bool imprimir_vencedor(void);
int encontrar_minimo(void);
bool eh_empate(int min);
void eliminar(int min);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Uso: runoff [candidato ...]\n");
        return 1;
    }

    quantidade_candidatos = argc - 1;
    if (quantidade_candidatos > MAX_CANDIDATOS)
    {
        printf("Número máximo de candidatos é %i\n", MAX_CANDIDATOS);
        return 2;
    }

    for (int i = 0; i < quantidade_candidatos; i++)
    {
        candidatos[i].nome = argv[i + 1];
        candidatos[i].votos = 0;
        candidatos[i].eliminado = false;
    }

    quantidade_eleitores = get_int("Número de eleitores: ");
    if (quantidade_eleitores > MAX_ELEITORES)
    {
        printf("Número máximo de eleitores é %i\n", MAX_ELEITORES);
        return 3;
    }

    for (int i = 0; i < quantidade_eleitores; i++)
    {
        for (int j = 0; j < quantidade_candidatos; j++)
        {
            string nome = get_string("Voto %i: ", j + 1);

            if (!votar(i, j, nome))
            {
                printf("Voto inválido.\n");
                return 4;
            }
        }
        printf("\n");
    }

    while (true)
    {
        tabular();

        bool venceu = imprimir_vencedor();
        if (venceu)
        {
            break;
        }

        int min = encontrar_minimo();
        bool empate = eh_empate(min);

        if (empate)
        {
            for (int i = 0; i < quantidade_candidatos; i++)
            {
                if (!candidatos[i].eliminado)
                {
                    printf("%s\n", candidatos[i].nome);
                }
            }
            break;
        }

        eliminar(min);

        for (int i = 0; i < quantidade_candidatos; i++)
        {
            candidatos[i].votos = 0;
        }
    }

    return 0;
}

bool votar(int eleitor, int rank, string nome)
{
    for (int i = 0; i < quantidade_candidatos; i++)
    {
        if (strcmp(candidatos[i].nome, nome) == 0)
        {
            preferencias[eleitor][rank] = i;
            return true;
        }
    }
    return false;
}

void tabular(void)
{
    for (int i = 0; i < quantidade_eleitores; i++)
    {
        for (int j = 0; j < quantidade_candidatos; j++)
        {
            int indice = preferencias[i][j];
            if (!candidatos[indice].eliminado)
            {
                candidatos[indice].votos++;
                break;
            }
        }
    }
}

bool imprimir_vencedor(void)
{
    int maioria = quantidade_eleitores / 2;
    for (int i = 0; i < quantidade_candidatos; i++)
    {
        if (candidatos[i].votos > maioria)
        {
            printf("Vencedor: %s\n", candidatos[i].nome);
            return true;
        }
    }
    return false;
}

int encontrar_minimo(void)
{
    int votos_minimos = 1000000;
    for (int i = 0; i < quantidade_candidatos; i++)
    {
        if (!candidatos[i].eliminado && candidatos[i].votos < votos_minimos)
        {
            votos_minimos = candidatos[i].votos;
        }
    }
    return votos_minimos;
}

bool eh_empate(int min)
{
    for (int i = 0; i < quantidade_candidatos; i++)
    {
        if (!candidatos[i].eliminado && candidatos[i].votos != min)
        {
            return false;
        }
    }
    return true;
}

void eliminar(int min)
{
    for (int i = 0; i < quantidade_candidatos; i++)
    {
        if (!candidatos[i].eliminado && candidatos[i].votos == min)
        {
            candidatos[i].eliminado = true;
        }
    }
}
