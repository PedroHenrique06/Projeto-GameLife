/**
 * LLSeq class implementation.
 *
 */
#include "life.h"
#include <fstream>


namespace life {

// Construtor padrão.
LifeCfg::LifeCfg(uint L, uint C) {
  m_linhas = L;
  m_colunas = C;

  m_matriz_celulas.reserve(L*C);
  m_matriz_caracteres_current.reserve(L*C);
  m_matriz_caracteres_next.reserve(L*C);
}


// Cria o mapa inicial de células.
void LifeCfg::set_alive(std::fstream &file) {
  file >> m_caractere;

  std::string linha_entrada;
  uint int_lin = 0;
    while (getline(file, linha_entrada)) {
    if(int_lin == m_linhas) break;
      
    if (linha_entrada.length() > 0) {
      for (uint j = 0; j < m_colunas; j++) {
        if (j < linha_entrada.length()) {
          if(linha_entrada[j] != m_caractere){
            m_matriz_caracteres_current[int_lin * m_colunas + j] = 0;
          }else{
            m_matriz_caracteres_current[int_lin * m_colunas + j] = 1;
          }
        }
        else{
          m_matriz_caracteres_current[int_lin * m_colunas + j] = 0;
        }
      }
      int_lin++;
    }
  }

  /*
    caso o a quantidade de linhas de entrada (m_linhas)
    seja maior que as linhas do arquivo de entrada, serão
    adiconadas na matriz as linhas que faltam.
  */
  if(int_lin < m_linhas){
    for (uint lin = int_lin; lin < m_linhas; lin++){
      for (uint col = 0; col < m_colunas; col++){
        m_matriz_caracteres_current[int_lin * m_colunas + col] = 0;
      }
    }
  }
  
  //alimentando matriz que representará a próxima geração! 
  for(uint x = 0; x < (m_linhas*m_colunas); x++){
    m_matriz_caracteres_next[x] = m_matriz_caracteres_current[x];
  }
  //m_linhas = int_lin;
  file.close();
}

// Prepara a matriz para o print.
void LifeCfg::prepare_matrix(void){
  for(uint y = 0; y < (m_linhas*m_colunas); y++){
    if(m_matriz_caracteres_current[y] == 1){
      m_matriz_celulas[y] = m_caractere;
    } else m_matriz_celulas[y] = ' ';
  }
}

// Contagem de vizinhos vivos.
int LifeCfg::count_neighbors(uint il, uint jc) const{
  int num_vizinhos_vivos = 0;
    
  if(il == 0 && jc == 0){
    if(m_matriz_caracteres_current[(il)*m_colunas+(jc+1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il+1)*m_colunas+(jc + 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il+1)*m_colunas+(jc)] == 1){
      num_vizinhos_vivos += 1;
    }
  }
  else if(il == 0 && jc == (m_colunas-1)){
    if(m_matriz_caracteres_current[(il)*m_colunas+(jc-1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il+1)*m_colunas+(jc - 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il+1)*m_colunas+(jc)] == 1){
      num_vizinhos_vivos += 1;
    }
  }

  else if(il == (m_linhas-1) && jc == 0){
    if(m_matriz_caracteres_current[(il)*m_colunas+(jc+1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il-1)*m_colunas+(jc + 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il-1)*m_colunas+(jc)] == 1){
      num_vizinhos_vivos += 1;
    }
  }

  else if(il == (m_linhas-1) && jc == (m_colunas-1)){
    if(m_matriz_caracteres_current[(il)*m_colunas+(jc-1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il-1)*m_colunas+(jc - 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il-1)*m_colunas+(jc)] == 1){
      num_vizinhos_vivos += 1;
    }
  }
  //teste para não procurar vizinhos em linhas "negativas"
  else if(il == 0){
    if(m_matriz_caracteres_current[il*m_colunas+(jc + 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[il*m_colunas+(jc - 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il+1)*m_colunas+(jc - 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il+1)*m_colunas+(jc)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il+1)*m_colunas+(jc + 1)] == 1){
      num_vizinhos_vivos += 1;
    }
  }

  //teste para não procurar vizinhos em colunas "negativas"
  else if(jc == 0){
    if(m_matriz_caracteres_current[il*m_colunas+(jc + 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il+1)*m_colunas+(jc + 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il-1)*m_colunas+(jc + 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il+1)*m_colunas+(jc)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il-1)*m_colunas+(jc)] == 1){
      num_vizinhos_vivos += 1;
    }
  }

  else if(il == (m_linhas-1)){
    if(m_matriz_caracteres_current[il*m_colunas+(jc + 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il)*m_colunas+(jc - 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il-1)*m_colunas+(jc + 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il-1)*m_colunas+(jc - 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il-1)*m_colunas+(jc)] == 1){
      num_vizinhos_vivos += 1;
    }
  }


  else if(jc == (m_colunas-1)){
    if(m_matriz_caracteres_current[il*m_colunas+(jc-1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il-1)*m_colunas+(jc)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il+1)*m_colunas+(jc)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il+1)*m_colunas+(jc - 1)] == 1){
      num_vizinhos_vivos += 1;
    }
    if(m_matriz_caracteres_current[(il-1)*m_colunas+(jc - 1)] == 1){
      num_vizinhos_vivos += 1;
    }
  }
  
  else{
    for(int i = -1; i < 2; i++){
      for(int j = -1; j < 2; j++){
        num_vizinhos_vivos += m_matriz_caracteres_current[(il+(i))*m_colunas+(jc+(j))];
      }
    }
    num_vizinhos_vivos -=  m_matriz_caracteres_current[(il)*m_colunas+(jc)];
  }
  return num_vizinhos_vivos;
}

void LifeCfg::update(){
  
  for (uint il = 0; il < m_linhas; il++) {
    for (uint jc = 0; jc < m_colunas; jc++) {
      //contar vizinhos
      int num_vizinhos_vivos = count_neighbors(il, jc);

      if(m_matriz_caracteres_current[il*m_colunas+jc] == 1){
        //celula não vai sobreviver;
        if(num_vizinhos_vivos != 2 && num_vizinhos_vivos != 3){
          m_matriz_caracteres_next[il*m_colunas+jc] = 0;
        }
      }else{
        //celula passa a viver
        if(num_vizinhos_vivos == 3){
          m_matriz_caracteres_next[il*m_colunas+jc] = 1;
        }
      }
    }
  }

  
  //atualizando matriz atual
  for(uint x = 0; x < (m_linhas*m_colunas); x++){
    m_matriz_caracteres_current[x] = m_matriz_caracteres_next[x];
  }
}

bool LifeCfg::extinct() const{
  bool is_Extinct;
  for(uint y = 0; y < (m_linhas*m_colunas); y++){
    if(m_matriz_caracteres_next[y] == 1){
      is_Extinct = false;
      break;
    } else{
      is_Extinct = true;
    } 
  }
  return is_Extinct;
}

/*
 * Minha ideia seria criar uma m_matriz_caracteres_current 'char' para conter a saída de
 * cada configuração nova Então eu manteria duas matrizes, uma de células e uma
 * de caracteres A matriz de células abasteceria a de caracteres
 */

// Mostra a configuração atual
void LifeCfg::show_configuration() {
  //std::cout << (m_matriz_caracteres_current.capacity()) << '\n';
  for (uint il = 0; il < m_linhas; il++) {
    std::cout << "[ ";
    for (uint jc = 0; jc < m_colunas; jc++) {
      std::cout << m_matriz_celulas[il*m_colunas+jc];
    }
    std::cout << " ]\n";
  }
  std::cout << "\n";
}

// Operador de atribuição
LifeCfg &LifeCfg::operator=(const LifeCfg &_rhs) {
  this->m_matriz_celulas = _rhs.m_matriz_celulas;
  this->m_matriz_caracteres_current = _rhs.m_matriz_caracteres_current;
  this->m_linhas = _rhs.m_linhas;
  this->m_colunas = _rhs.m_colunas;
  return *this;
}
uint LifeCfg::rows(void) const { return m_linhas; }
uint LifeCfg::cols(void) const { return m_colunas; }

// Destrutor.
LifeCfg::~LifeCfg(){ /* empty */ };


} // namespace life
