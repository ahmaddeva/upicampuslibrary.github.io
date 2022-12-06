#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>

using namespace std;
struct buku{
    string judul, pengarang, tahun_terbit, kode_buku; 
};
int getOption();
int getBook();
void login();

int main()
{
    system("cls");
    login();
    label_choice:
    int choice = getOption();
    enum option{BUKU = 1, PEMINJAMAN, PENGEMBALIAN, KELUAR};

    // ANCHOR Perubahan buku manual menjadi database

    while(choice != KELUAR){
        switch (choice)
        {
        case BUKU: {
            int book_choice = getBook();
            while(book_choice != 4){
                // List Buku

                int this_book = book_choice;
                //manual
                string buku1 = "Your Name";
                string buku2 = "Weathering With You";
                string buku3 = "Re:ZERO";
                
                ofstream filePeminjaman;
                ifstream fileBuku;
                string buku, pengarang ,line;
                if (book_choice == this_book)
                {
                    filePeminjaman.open("data_peminjaman.txt", ios::app);
                    fileBuku.open("data_buku.txt", ios::app);

                    ifstream buku_data("data_buku.txt");

                    int i = 0;
                    while (!buku_data.eof())
                    {
                        getline(buku_data, line);
                        stringstream ss(line);
                        getline(ss, buku, ',');
                        getline(ss, pengarang, ',');

                        if (i == this_book - 1)
                        {
                            filePeminjaman << buku << ",";
                            filePeminjaman << "\t" << __DATE__ << endl;
                            filePeminjaman.close();
                            cout << "Anda telah meminjam buku " << buku << " | " << pengarang << "." << endl;
                            fileBuku.close();
                            cout << "Tanggal Peminjaman: " << __DATE__ << endl;
                            system("pause");
                            goto label_choice;
                        } 
                        
                        i++;
                    }
                    cout << "Buku tidak ditemukan"<< endl;
                    system("pause");
                    goto label_choice;



                    // bool isBook = false;
                    // int i = 0;
                    // while (!isBook)
                    // {
                    //     getline(fileBuku, buku);
                    //     if (i == this_book - 1)
                    //     {
                    //         filePeminjaman << buku << ",";
                    //         filePeminjaman << "\t" << __DATE__ << endl;
                    //         filePeminjaman.close();
                    //         cout << "Anda telah meminjam buku " << buku << "." << endl;
                    //         cout << "Tanggal Peminjaman: " << __DATE__ << endl;
                    //         isBook = true;
                    //     }
                    //     i++;
                    // }
                    
                }
                // if (book_choice == 2)
                // {
                //     filePeminjaman.open("data_peminjaman.txt", ios::app);
                //     filePeminjaman << buku2 << ",";
                //     filePeminjaman << "\t" << __DATE__ << endl;
                //     filePeminjaman.close();
                //     cout << "Anda telah meminjam buku " << buku2 << "." << endl;
                //     cout << "Tanggal Peminjaman: " << __DATE__ << endl;
                //     system("pause");
                //     goto label_choice;
                // }
                // if (book_choice == 3)
                // {
                //     filePeminjaman.open("data_peminjaman.txt", ios::app);
                //     filePeminjaman << buku3 << ",";
                //     filePeminjaman << "\t\t" << __DATE__ << endl;
                //     filePeminjaman.close();
                //     cout << "Anda telah meminjam buku " << buku3 << "." << endl;
                //     cout << "Tanggal Peminjaman: " << __DATE__ << endl;
                //     system("pause");
                //     goto label_choice;
                // }
            }
            cout << "Terima kasih dan sampai jumpa!";   
            system("pause");
            goto label_choice;               
        }break;
        
        case PEMINJAMAN: {
            string line;
            ifstream file("data_peminjaman.txt");
            string judul, tanggal_peminjaman;
            system("cls");
            cout << "Tabel Peminjaman"<< endl; 
            cout << "=========================================="<< endl; 
            cout << "Judul Buku\t\t" << "Tanggal Peminjaman"<< endl; 
            cout << "=========================================="<< endl; 
            while(getline(file, line)){
                stringstream ss(line);
                getline(ss, judul, ',');
                getline(ss, tanggal_peminjaman, ',');

                cout << judul << " " << tanggal_peminjaman << endl;
            }
            file.close();
            cout << endl;
            system("pause");
            goto label_choice;
        }break; 
        
        case PENGEMBALIAN: {
            cout << "hello world" << endl;
            system("pause");
            goto label_choice;
        }break; 
        
        default:
            cout << "Masukkan pilihan yang benar" << endl;
            break;
        }
    }
    cout << "Terima kasih dan sampai jumpa!" << endl;
    cin.get();
    return 0;
}

void login(){
    string lUsername, username, lPassword, password, nama, line;
    int count;
    cout << "====================" << endl;
    cout << "Welcome!" << endl;
    cout << "====================" << endl;
    cout << "Username: ";
    cin >> lUsername;
    cout << "Password: ";
    cin >> lPassword;

    // ANCHOR Memperbaiki bug sistem login
    ifstream input("data_mahasiswa.txt");
    while(!input.eof()){
        getline(input, line);
        stringstream ss(line);
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, nama, ',');
        if (username == lUsername && password == lPassword)
        {
            count = 1;
            system("cls");
            cout << "\nLogin berhasil!" << endl;
            system("pause");
            continue;
            input.close();
        }
    }
    if (count != 1){        
        cout << "\nLogin anda salah, coba lagi!" << endl;
        system("pause");
        main();
    }
}

int getOption(){
    int choice;
    system("cls");
    cout << "=======================" << endl;
    cout << "Aplikasi Perpustakaan" << endl;
    cout << "=======================" << endl;
    cout << "1. Pilih buku" << endl;
    cout << "2. Daftar Peminjaman" << endl;
    cout << "3. Pengembalian" << endl;
    cout << "4. Keluar" << endl;
    cout << "=======================" << endl;
    cout << "Pilih menu (1-4): ";
    cin >> choice;
    return choice;
}
int getBook(){
    int choice;
    system("cls");
    //manual
    cout << "\nPilih Buku" << endl;
    cout << "=======================" << endl;
    cout << "1. Your Name" << endl;
    cout << "2. Weathering With You" << endl;
    cout << "3. Re:ZERO" << endl;
    cout << "4. Kembali ke laman utama" << endl;
    cout << "=======================" << endl;
    cout << "Pilih menu (1-4): ";
    cin >> choice;
    return choice;
}