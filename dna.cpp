//include 
#include<bitset>
#include<iostream>
#include<cstring>
#include<fstream>
#include<string>

using namespace std;

#define BASE_MASK 0x3 /* binary: 11 */

enum
{
    BASE_A = 0x0, /* binary: 00 */
    BASE_C = 0x1, /* binary: 01 */
    BASE_G = 0x2, /* binary: 10 */
    BASE_T = 0x3, /* binary: 11 */
};

class dnaBitset
{
    public:
        dnaBitset(const char* dna_str, const size_t dna_len){
           m_len = dna_len;
 
        /* number of bytes necessary to store dna_str as a bitset */
            size_t dna_bytes = (dna_len / 4) + (dna_len % 4 != 0);
 
            m_data = new uint8_t[dna_bytes];
 
            std::memset(m_data, 0, dna_bytes);
 
        /* for each base of the DNA sequence */
            for (size_t i = 0; i < dna_len; ++i)
            {
                uint8_t shift = 6 - 2 * (i % 4);
    
                switch (dna_str[i])
                {
                    case 'A':
                        m_data[i / 4] |= BASE_A << shift;
                        break;
                    case 'C':
                        m_data[i / 4] |= BASE_C << shift;
                        break;
                    case 'G':
                        m_data[i / 4] |= BASE_G << shift;
                        break;
                    case 'T':
                        m_data[i / 4] |= BASE_T << shift;
                        break;
                    default:
                        throw std::invalid_argument("invalid DNA base");
                }
    
                shift = (shift == 0) ? 6 : shift - 2;
            }
        }
        ~dnaBitset(){
            delete[] m_data;
        }
        char* to_string() const{
            char* dna_str = new char[m_len + 1];
    
            /* for each base of the DNA sequence */
            for (size_t i = 0; i < m_len; ++i)
            {
                uint8_t shift = 6 - 2 * (i % 4);
                uint8_t mask = BASE_MASK << shift;
    
                /* get the i-th DNA base */
                uint8_t base = (m_data[i / 4] & mask) >> shift;
    
                switch (base)
                {
                    case BASE_A:
                        dna_str[i] = 'A';
                        break;
                    case BASE_C:
                        dna_str[i] = 'C';
                        break;
                    case BASE_G:
                        dna_str[i] = 'G';
                        break;
                    case BASE_T:
                        dna_str[i] = 'T';
                        break;
                    default:
                        throw std::runtime_error("invalid DNA base");
                }
            }
    
            dna_str[m_len] = '\0';
            return dna_str;
        }
    private:
        size_t m_len;
        uint8_t* m_data;
};



int main(){
    string dna_str;
    ifstream file("input.txt");
    if(file.is_open()){
        getline(file, dna_str);
        file.close();
    }
    else{
        cout<<"Unable to open file";
    }
    dnaBitset dna(dna_str.c_str(), dna_str.length());

}