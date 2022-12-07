#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>
#include <limits>
using namespace std;

struct buku{
    string judul, pengarang; 
};
struct mahasiswa{
    string nama, password, NIM; 
};
int menu();
int menu2();
int menuBuku();
void login();
void registrasi();

int main()
{
    system("cls");
    int pilih = menu();
    switch (pilih)
    {
    case 1:
        registrasi();
        break;
    case 2: 
        login();
        break;
    case 3:
        return 0;    
    default:
        break;
    }
    label_pilih:
    int pilih2 = menu2();
    enum option{BUKU = 1, PEMINJAMAN, PENGEMBALIAN, KELUAR};

    // ANCHOR Perubahan buku manual menjadi database
    while(pilih2 != KELUAR){
        switch (pilih2)
        {
        case BUKU: {
            int book_pilih = menuBuku();
            while(book_pilih != 5 && book_pilih != 4){
                int this_book = book_pilih;
                
                ofstream filePeminjaman;
                string buku, pengarang ,line;
                if (book_pilih == this_book)
                {
                    filePeminjaman.open("data_peminjaman.txt", ios::app);
                    ifstream buku_data;
                    buku_data.open("data_buku.txt");
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
                            buku_data.close();
                            cout << "Tanggal Peminjaman: " << __DATE__ << endl;
                            system("pause");
                            goto label_pilih;
                        } 
                        i++;
                    }
                    cout << "Buku tidak ditemukan"<< endl;
                    system("pause");
                    goto label_pilih;
                }
            }
            if (book_pilih == 4){
                string aBuku[5];
                string judul, line, buku, pengarang, pBuku;
                int hasilCari;
                ifstream buku_data;
                cout << "Masukkan judul buku: ";
                cin >> judul;
                buku_data.open("data_buku.txt");
                while (!buku_data.eof())
                    {
                        getline(buku_data, line);
                        stringstream ss(line);
                        getline(ss, buku, ',');
                        getline(ss, pengarang, ',');
                        if (judul == buku)
                        {
                            hasilCari = 1;
                            pBuku = pengarang;
                        }
                    }
                buku_data.close();
                if (hasilCari == 0){
                    cout << "Buku tidak ditemukan" << endl;
                } else {
                    char pilih = 'n';
                    cout << "Buku " << judul << " ditemukan" << endl;
                    cout << "Apakah anda ingin meminjam buku tersebut? (y/n)" << endl;
                    cin >> pilih;
                    if (pilih == 'y'){
                        ofstream filePeminjaman;
                        filePeminjaman.open("data_peminjaman.txt", ios::app);
                        filePeminjaman << "\n";
                        filePeminjaman << judul << ",";
                        filePeminjaman << "\t" << __DATE__ << endl;
                        filePeminjaman.close();
                        cout << "Anda telah meminjam buku " << judul << " | " << pBuku << "." << endl;
                        cout << "Tanggal Peminjaman: " << __DATE__ << endl;
                    } else {
                        system("pause");
                        goto label_pilih;
                    }
                }
            } 
            // cout << "Terima kasih dan sampai jumpa!";   
            system("pause");
            goto label_pilih;               
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
            goto label_pilih;
        }break; 
        
        case PENGEMBALIAN: {
            cout << "hello world" << endl;
            system("pause");
            goto label_pilih;
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
    int count = 0;
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
void registrasi(){
    mahasiswa mhs;
    // input data
    cout << "Masukkan nama: ";
    getline(cin, mhs.nama);
    cout << "Masukkan NIM: ";
    getline(cin, mhs.NIM);
    cout << "Masukkan Password: ";
    getline(cin, mhs.password);

    ofstream fileRegister;
    fileRegister.open("data_mahasiswa.txt", ios::app);
    fileRegister << "\n";
    fileRegister << mhs.NIM;
    fileRegister << ",";
    fileRegister << mhs.password;
    fileRegister << ",";
    fileRegister << mhs.nama;
    fileRegister.close();
    main();
}
int menu(){
    int pilih;
    system("cls");
    cout << "=======================" << endl;
    cout << "Aplikasi Perpustakaan" << endl;
    cout << "=======================" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Keluar" << endl;
    cout << "=======================" << endl;
    cout << "Pilih menu (1-3): ";
    cin >> pilih;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    return pilih;
}

int menu2(){
    int pilih;
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
    cin >> pilih;
    return pilih;
}
int menuBuku(){
    int pilih;
    system("cls");
    //manual
    cout << "\nPilih Buku" << endl;
    cout << "=======================" << endl;
    cout << "1. Your Name" << endl;
    cout << "2. Weathering With You" << endl;
    cout << "3. Re:ZERO" << endl;
    cout << "4. Cari Buku" << endl;
    cout << "5. Kembali ke laman utama" << endl;
    cout << "=======================" << endl;
    cout << "Pilih menu (1-5): ";
    cin >> pilih;
    return pilih;
}