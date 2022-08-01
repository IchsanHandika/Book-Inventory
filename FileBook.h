#ifndef _FILEBOOK_H
#define _FILEBOOK_H
#include <string>

using namespace std;

class FileBook {
public: 
    string Judul, Penulis, Tahun, Genre;
    
void AddBook(string file);
    
void DeleteBook(string file);
    
void EditBook(string file);
    
void BookList(string file);
    
void SearchBook(string file);

bool findBook(string Judul, string file);
};

#endif //_FILEBOOK_H