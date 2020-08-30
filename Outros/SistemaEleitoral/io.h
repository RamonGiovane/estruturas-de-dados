#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

int lerInteiro(const char *txt);
void lerString(const char *txt, char *retorno, int tamanho);
void quebrarString(char *s, const char *delimitador, char *resultado[], int size_resultado);
bool invalido(const char *dado);
bool votoValido(int candidato, int votosCandidato);
bool votoInvalido(void);

#endif
