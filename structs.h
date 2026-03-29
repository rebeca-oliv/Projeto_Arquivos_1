typedef struct {
  char *status;
  int topo;
  int proxRRN;
  int nroEstacoes;
  int nroParesEstacoes;
} RegistroCabecalho;

typedef struct {
  char *removido;
  int proximo;
  int codEstacao;
  int codLinha;
  int codProxEstacao;
  int distProxEstacao;
  int codLinhaIntegra;
  int codEstIntegra;
  int tamNomeEstacao;
  char *nomeEstacao;
  int tamNomeLinha;
  char *nomeLinha;
} RegistroDado;

/*! 
 * @brief Desaloca os campos dinâmicamente alocados do registro de dados.
 * 
 * @param r Registro cujos recursos devem ser liberados.
 */
void free_reg_dados(RegistroDado* r);

/*! 
 * @brief Desaloca os campos dinâmicamente alocados do registro de cabeçalho.
 * 
 * @param h header cujos recursos devem ser liberados.
 */
void free_reg_cab(RegistroCabecalho* h);