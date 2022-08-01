#include "Control.h"
#include "FileBook.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
FileBook buku;

void Control::MakeFileBook() {
    string line;

    cout << "Silahkan membuat akun terlebih dahulu" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Username : ";
    cin >> username;

    ifstream Uname;
    Uname.open("list FileBook.txt");
    while(getline(Uname, line))
    {
        if(line == username)
        {
            cout << "---Username sudah terpakai---" << endl;
            cout << "--Silahkan pilih username lain!--" << endl << endl;
            return;
        }
    }
    cout << "Password : ";
    cin >> password;

    ofstream myFile;
    myFile.open("list FileBook.txt", ios::app);
    myFile << username << endl;
    myFile << password << endl << endl;
    cout << "--File Anda berhasil dibuat--" << endl << endl;
    myFile.close();
    
    string fileName = "buku " + username + ".txt";
    myFile.open(fileName, ios::out);
    FileBookLoop(fileName);
}

void Control::ChooseFileBook() {
    string line;
    bool find = false;
    bool status = false;

    label:
    cout << "Username : ";
    cin >> username;
    loop:
    cout << "Password : ";
    cin >> password;

    ifstream myFile;
    myFile.open("list FileBook.txt");
    while(getline(myFile, line))
    {
        if(find == true){
            if(line == password){
                status = true;
            }
        }
        if(line == username){
            find = true;
        }
    }
    myFile.close();

    if(find == true){
        if(status == true){
            cout << "\n--Password benar!--\n\n";
            string fileName = "buku " + username + ".txt";
            FileBookLoop(fileName);
        }
        else{
            cout << "\n--Password salah!--\n\n";
            goto loop;
        }
    }
    else{
        cout << "\n--Username tidak ditemukkan--\n\n";
        goto label;
    }
}

void Control::DeleteFileBook() {
    string line;
    string file_list = "list Filebook.txt";
	string file_temp = "temp.txt";
	const char* arr_file_list = file_list.c_str();
	const char* arr_file_temp = file_temp.c_str();
    bool find = false;
    bool status = false;
	int i=0;

    label:
    cout << "Username : ";
    cin >> username;
    loop:
    cout << "Password : ";
    cin >> password;

    ifstream myFile;
    myFile.open("list FileBook.txt");
    while(getline(myFile, line))
    {
        if(find == true){
            if(line == password){
                status = true;
            }
        }
        if(line == username){
            find = true;
        }
    }
    myFile.close();

    if(find == true){
        if(status == true){
            cout << "\n--Password benar!--\n\n";
            
            remove(arr_file_temp);
            ifstream myFile;
            ofstream temp;
            myFile.open(file_list);
            temp.open(file_temp, ios::app);
            while(getline(myFile, line))
            {
                if(line != username && i==0){
                    temp << line << endl;
                }
                else if(line == username){
                    i += 3;
                }
                if(i > 0){
                    i -= 1;
                }
            }
            myFile.close(); temp.close();

            remove(arr_file_list);
            rename(arr_file_temp, arr_file_list);

            string fileName = "buku " + username + ".txt";
            const char* file = fileName.c_str();
            remove(file);
            cout << "--Akun terhapus--" << endl << endl;
        }
        else{
            cout << "\n--Password salah!--\n\n";
            goto loop;
        }
    }
    else{
        cout << "\n--Username tidak ditemukkan--\n";
        goto label;
    }
    CommandLoop();
}

void Control::CommandLoop() {
    int input;

    cout << "==================" << endl;
    cout << "1. Bikin File Book" << endl;
    cout << "2. Pilih File Book" << endl;
    cout << "3. Hapus File Book" << endl;
    cout << "4. Selesai" << endl;
    cout << "==================" << endl;
    cout << "pilih[1-3] : ";
    cin >> input;
    cout << endl;

    while(input !=4){
        switch(input){
            case 1:
                MakeFileBook();
                break;
            case 2:
                ChooseFileBook();
                break;
            case 3:
                DeleteFileBook();
                break;
        }
    }
    cout << "\nTerima kasih!" << endl;
    exit(0);
}

void Control::FileBookLoop(string file) {
    int input;

    cout << "\tSELAMAT DATANG DI FILEBOOK ANDA" << endl;
    cout << "============================================" << endl;
    cout << "1. Tambah buku baru" << endl;
    cout << "2. Hapus buku yang sudah ada" << endl;
    cout << "3. Ubah data buku yang sudah ada" << endl;
    cout << "4. Perlihatkan buku yang tersimpan pada file" << endl;
    cout << "5. Cari ketersediaan buku" << endl;
    cout << "6. Kembali ke menu awal (logout)" << endl;
    cout << "7. Selesai" << endl;
    cout << "============================================" << endl;
    cout << "Pilih[1-6] : ";
    cin >> input;
    cin.ignore();
    
    while(input !=7){
        switch(input){
            case 1:
                buku.AddBook(file);
                break;
            case 2:
                buku.DeleteBook(file);
                break;
            case 3:
                buku.EditBook(file);
                break;
            case 4:
                buku.BookList(file);
                break;
            case 5:
                buku.SearchBook(file);
                break;
            case 6:
                cout << endl;
                CommandLoop();
                break;
        }
    }
    cout << "Terima kasih!" <<endl;
    exit(0);
}