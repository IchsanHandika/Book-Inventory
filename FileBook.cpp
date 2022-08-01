#include <iostream>
#include <fstream>
#include <string>
#include "FileBook.h"
#include "Control.h"

using namespace std;
Control back;

void FileBook::AddBook(string file) {
    cout << "\n--Silahkan isi data berikut!--" << endl;
    cout << "================================" << endl;
    cout << "Judul buku : ";
    getline(cin, Judul);
    cout << "Penulis buku : ";
    getline(cin, Penulis);
    cout << "Tahun terbit : ";
    getline(cin, Tahun);
    cout << "Genre buku : ";
    getline(cin, Genre);

    fstream myFile;
    myFile.open(file, ios::app);
    myFile << Judul << "\n" << Penulis << "\n";
    myFile << Tahun << "\n" << Genre << endl << endl;
    myFile.close();

    cout << "================================" << endl;
    cout << "--Buku berhasil ditambahkan--" << endl << endl;

    string input;
    label:
    cout << "Apakah ada buku yang ingin ditambahkan lagi?[Y/N] : ";
    cin >> input;
    cin.ignore();

    if((input == "Y")|(input == "y")){
        return;
    }
    else if((input == "N")|(input == "n")){
        cout << "\n--Anda akan kembali ke halaman awal setelah login--";
        cout << endl << endl;
        back.FileBookLoop(file);
    }
    else{
        cout << "\n--Terdapat kesalahan input--\n\n";
        goto label;
    }
}

void FileBook::DeleteBook(string file) {
    cout << "\n--Tuliskan judul buku yang ingin dihapus!--" << endl;
    cout << " Judul buku : ";
    getline(cin, Judul);

    bool check = false;
    check = findBook(Judul, file);
    if(check == false){
        cout << "\n--Judul buku tidak ditemukkan" << endl << endl;
        return;
    }
    string file_book = file; 
    string file_temp = "temp.txt";
    const char* arr_file_book = file_book.c_str();
    const char* arr_file_temp = file_temp.c_str();
    int i = 0;
   
    remove(arr_file_temp);
    ifstream myFile;
    ofstream temp;
    string line;

    myFile.open(file_book);
    temp.open(file_temp, ios::app);
    while (getline(myFile, line))
    {
        if(line != Judul && i==0){
            temp << line << endl;
        }
        else if(line == Judul){
            i += 5;
        }
        if(i > 0){
           i -= 1;
        }
    }
    myFile.close(); temp.close();

    remove(arr_file_book);
    rename(arr_file_temp, arr_file_book);

    cout << "--Buku telah dihapus dari file--" << endl;
}

void FileBook::EditBook(string file) {
    bool check = false;
    string line;
    string file_fb = file;
	string file_temp = "temp.txt";
	const char* arr_file_fb = file_fb.c_str();
	const char* arr_file_temp = file_temp.c_str();
    int i = 0; int j = 0;
    ifstream myFile;
    ofstream temp;
    myFile.open(file_fb);
    temp.open(file_temp, ios::app);

    cout << "\nJudul buku yang akan diedit: ";
	getline(cin, line);

    check = findBook(Judul, file);

    cout << "============================================" << endl;
    if(check == false){
	    cout << "\n--Buku tidak ditemukan--\n";
	    return;
	}
	else{
		cout << "Judul buku diedit menjadi..." << endl;
		cout << "Judul buku : ";
        getline(cin, Judul);
        cout << "Penulis buku : ";
        getline(cin, Penulis);
        cout << "Tahun terbit : ";
        getline(cin, Tahun);
        cout << "Genre buku : ";
        getline(cin, Genre);

        remove(arr_file_temp);
		while (getline(myFile, line))
        {
			if (line != Judul && i == 0){
                temp << line << endl;
            }
			switch (j){
			case 1:
				temp << Penulis << endl;
				j++;
				break;
			case 2:
				temp << Tahun << endl;
				j++;
				break;
			case 3:
				temp << Genre << endl;
				j = 0;
				break;
			}
			if (line == Judul){
				temp << Judul << endl;
				j = 1;
				i += 4;
			}
			if (i > 0)
				i -= 1;
		}
        myFile.close(); temp.close();

		remove(arr_file_fb);
		rename(arr_file_temp, arr_file_fb);
    }
    cout << "\n--Data pada file telah diedit--\n\n";
    back.FileBookLoop(file);
}

void FileBook::BookList(string file) {
    int i = 1;
    int j = 1;
    string line;

    cout << "============================================" << endl;
    ifstream myFile;
    myFile.open(file);
    while(!myFile.eof()){
        getline(myFile, line);
        switch(i){
            case 1:
                Judul = line;
                break;
            case 2:
                Penulis = line;
                break;
            case 3:
                Tahun = line;
                break;
            case 4:
                Genre = line;
                cout << "[" << j++ << "] ";
                cout << "Judul buku   : "<< Judul << endl;
                cout << "    Penulis buku : " << Penulis << endl;
                cout << "    Tahun terbit : " << Tahun << endl;
                cout << "    Genre buku   : " << Genre << endl << endl;;
                break;
        }
        if(i > 4){
            i = 0;
        }
        i++;
    }
    cout << "============================================\n\n";
    back.FileBookLoop(file);
}

void FileBook::SearchBook(string file) {
    bool check = false;
    string line;
    string input;
    int i = 0;

    cout << "\n--Tulis judul buku yang sedang Anda cari--" << endl;
    cout << "Judul buku : ";
    getline(cin, Judul);
    check = findBook(Judul, file);

    if(check == true){
        ifstream myFile;
        myFile.open(file);
        while(getline(myFile, line))
        {
            switch(i){
                case 1:
                    Penulis = line;
                    i++;
                    break;
                case 2:
                    Tahun = line;
                    i++;
                    break;
                case 3:
                    Genre = line;
                    cout <<"\n--Buku tersedia!--" << endl;
                    cout << "==================================\n";
                    cout << "Judul Buku   : " << Judul << endl;
                    cout << "Penulis Buku : " << Penulis << endl;
                    cout << "Tahun Terbit : " << Tahun << endl;
                    cout << "Genre Buku   : " << Genre << endl;
                    cout << "==================================\n";
                    i = 0;
                    break;
            }
            if(line == Judul){
                i = 1;
            }
        }
        myFile.close();
    }
    else{
        cout << "\n--Buku yang anda cari tidak tersedia--\n\n";
    }
    label:
    cout << "Apakah ada buku yang ingin dicari lagi? [Y/N] : " << endl;
    cin >> input;
    cin.ignore();

    if((input == "Y")|(input == "y")){
        return;
    }
    else if((input == "N")|(input == "n")){
        cout << "\n--Anda akan kembali ke halaman awal setelah login--\n\n";
        back.FileBookLoop(file);
    }
    else{
        cout << "\n--Terdapat kesalahan input--\n\n";
        goto label;
    }
}

bool FileBook::findBook(string Judul, string file){
    string line;

    ifstream findData;
    findData.open(file);
    while(getline(findData, Judul)){
        if(line == Judul){
            return true;
        }
    }
    return false;
}