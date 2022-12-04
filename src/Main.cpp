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

    while(choice != KELUAR){
        switch (choice)
        {
        case BUKU: {
            int book_choice = getBook();
            while(book_choice != 4){
                // List Buku
                //manual
                string buku1 = "Your Name";
                string buku2 = "Weathering With You";
                string buku3 = "Re:ZERO";
                
                ofstream filePeminjaman;
                if (book_choice == 1)
                {
                    filePeminjaman.open("data_peminjaman.txt", ios::app);
                    filePeminjaman << buku1 << ",";
                    filePeminjaman << "\t\t" << __DATE__ << endl;
                    filePeminjaman.close();
                    cout << "Anda telah meminjam buku " << buku1 << "." << endl;
                    cout << "Tanggal Peminjaman: " << __DATE__ << endl;
                    system("pause");
                    goto label_choice;
                }
                if (book_choice == 2)
                {
                    filePeminjaman.open("data_peminjaman.txt", ios::app);
                    filePeminjaman << buku2 << ",";
                    filePeminjaman << "\t" << __DATE__ << endl;
                    filePeminjaman.close();
                    cout << "Anda telah meminjam buku " << buku2 << "." << endl;
                    cout << "Tanggal Peminjaman: " << __DATE__ << endl;
                    system("pause");
                    goto label_choice;
                }
                if (book_choice == 3)
                {
                    filePeminjaman.open("data_peminjaman.txt", ios::app);
                    filePeminjaman << buku3 << ",";
                    filePeminjaman << "\t\t" << __DATE__ << endl;
                    filePeminjaman.close();
                    cout << "Anda telah meminjam buku " << buku3 << "." << endl;
                    cout << "Tanggal Peminjaman: " << __DATE__ << endl;
                    system("pause");
                    goto label_choice;
                }
            }
            cout << "Terima kasih dan sampai jumpa!";                  
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

    ifstream input("data_mahasiswa.txt");
    while(getline(input, line)){
        stringstream ss(line);
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, nama, ',');
        if (username == lUsername && password == lPassword)
        {
            count = 1;
            system("cls");
        }
        input.close();
        if (count == 1){
            continue;
        } else if( count != 1){
            cout << "\nLogin anda salah, coba lagi!" << endl;
            system("pause");
            main();
        }
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