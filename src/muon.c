#include <stdio.h>

void abrirbinario(char *ruta)
{
    FILE* f = fopen(ruta, "rb");
    if (f == NULL)
    {
        printf("error: el fichero no existe\n");
        return;
    }
    else
    {

        unsigned char buffer[4096];
        size_t bytes_leidos;

        while ((bytes_leidos = fread(buffer, 1, sizeof buffer, f)) > 0)
        {
            for (int i = 0; i < bytes_leidos; i++)
            {
                switch (buffer[i])
                {
                    case 0x90:
                        printf("NOP\n");
                        break;
                    case 0x55:
                        printf("PUSH EBP\n");
                        break;
                    case 0x5D:
                        printf("POP EBP\n");
                        break;
                    case 0xC3:
                        printf("RET\n");
                        break;
                    case 0xCC:
                        printf("INT 3\n");
                        break;
                    default:
                        printf("db 0x%02x\n", buffer[i]);
                        break;
                }
            }
        }

        if (ferror(f))
        {
            perror("Error al leer");
            fclose(f);
            return;
        }
        fclose(f);
    }
}

int main(int argc, char * argv[])
{

    if (argc != 2)
    {
        printf("error: uso muon <archivo binario>\n");
        return 1;
    }
    else
    {

        abrirbinario(argv[1]);
    }

    return 0;

}

