//! This class implements a life board in the Conway's Game of Life.
/*!
 * @file life.h
 *
 * @details Class Life, to simulate the Conway's Game of Life.
 *
 * @author	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2015, updated 2015-04-03
 * @update 2019, April 2nd.
 * @version     v1.1
 */

#ifndef _LIFE_H_
#define _LIFE_H_

#include <cassert>
#include <cstring>  // std::memcpy().
#include <iostream>
#include <set>
#include <sstream>  // std::ostringstream
#include <stdexcept>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;

using uint =  unsigned int;

// Está sem uso por enquanto.
class Cell{
    public:
        Cell(bool alive = false) {m_status = alive;}
        bool is_alive() const { return m_status;};
    private:    
        bool m_status; //indica se a célula está viva ou morta
};

namespace life {

/// A life configuration.
class LifeCfg {

   public:
    LifeCfg(uint, uint);
    ~LifeCfg();
    void set_alive(std::fstream&);
    void update(void);
    void prepare_matrix();
    void show_configuration();
    LifeCfg& operator=(const LifeCfg& _rhs);
    bool extinct(void) const;
    int count_neighbors(uint, uint) const;
    uint rows(void) const;
    uint cols(void) const;

    private:        
        std::vector<char> m_matriz_celulas;             //!< Matriz de células.
        std::vector<int> m_matriz_caracteres_current;   //!< Matriz de caracteres atual.
        std::vector<int> m_matriz_caracteres_next;      //!< Matriz de caracteres da próxima geração.
        uint m_linhas;                             //!< # de linhas.
        uint m_colunas;                            //!< # de colunas.
        char m_caractere;                               //!< Caractere que indica a existência de uma célula viva.
};

}  // namespace life

#endif
