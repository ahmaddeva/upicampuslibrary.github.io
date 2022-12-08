#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>
#include <limits>
#include <stdio.h>

using namespace std;

struct buku{
    string judul, pengarang; 
};

struct mahasiswa{
    string nama, password, NIM; 
};

// Active User
string lUsername, username, lPassword, password, nama, line;

int menu();
int menu2();
int menuBuku();
void login();
void registrasi();

int main()
{
    HOME:
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
        cout << "Masukan pilihan yang valid" << endl;
        system("pause");
        goto HOME;   
    default:
        cout << "Masukan pilihan yang valid" << endl;
        system("pause");
        goto HOME;
        break;
    }
    label_pilih:
    int pilih2 = menu2();
    enum option{BUKU = 1, PEMINJAMAN, PENGEMBALIAN, DAFTARPENGEMBALIAN, KELUAR};

    // ANCHOR Perubahan buku manual menjadi database
    while(pilih2 != KELUAR){
        switch (pilih2)
        {
        case BUKU: {
            int book_pilih = menuBuku();
            while(book_pilih != 0 && book_pilih != 5){
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
                            filePeminjaman << "\t" << __DATE__ << ",";
                            filePeminjaman << lUsername << endl;
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
            if (book_pilih == 0){
                
                ifstream buku_data;

                buku_data.open("data_buku.txt");
                string buku, pengarang ,id_buku, line;
                int i = 0, j = 0;
                string kotak_judulBuku[10], kotak_idBuku[10];

                while (getline(buku_data, line))
                {
                    stringstream ss(line);
                    getline(ss, buku, ',');
                    getline(ss, pengarang, ',');
                    getline(ss, id_buku, ',');
                    
                    kotak_judulBuku[i] = buku;
                    kotak_idBuku[i] = id_buku;

                    i++;
                }
                buku_data.close();

                string searchBuku;
                int k = 0, pilih;

                cin.clear();
                cin.sync();
                system("cls");
                cout << "Ketik judul atau kode buku yang dicari"<< endl;
                cout << "==================="<< endl;
                cout << "Masukan kata kunci : "; 
                getline(cin, searchBuku);

                for (int k = 0; k <= i; k++){
                    if (kotak_judulBuku[k] == searchBuku || kotak_idBuku[k] == searchBuku)
                    {
                         cout << "Buku " << kotak_judulBuku[k] << " ditemukan" << endl;
                         cout << "Apakah anda ingin meminjam buku tersebut (1/0)? ";
                         cin >> pilih;
                         if (pilih == 1)
                         {
                            ofstream filePeminjaman;
                            filePeminjaman.open("data_peminjaman.txt", ios::app);
                            filePeminjaman << kotak_judulBuku[k] << ",";
                            filePeminjaman << __DATE__ << ",";
                            filePeminjaman << lUsername << endl;
                            filePeminjaman.close();
                            cout << "Anda telah meminjam buku " << kotak_judulBuku[k] << " | " << kotak_idBuku[k] << "." << endl;
                            cout << "Tanggal Peminjaman: " << __DATE__ << endl;
                            filePeminjaman.close();
                            system("pause");
                            goto label_pilih;
                         }
                         else
                         {
                            system("pause");
                            goto label_pilih;
                         }
                    }
                }

                cout << "Buku tidak ditemukan"<<endl;
                system("pause");
                goto label_pilih;
            } 
 
            system("pause");
            goto label_pilih;               
        }break;
        
        case PEMINJAMAN: {
            string userNow;
            ifstream dataUser("data_mahasiswa.txt");
            while(!dataUser.eof()){
                getline(dataUser, line);
                stringstream ss(line);
                getline(ss, username, ',');
                getline(ss, password, ',');
                getline(ss, nama, ',');
                if (lUsername == username)
                {
                    userNow = username;
                }
            }

            string line;
            ifstream file("data_peminjaman.txt");
            string judul, tanggal_peminjaman, peminjam;
            system("cls");
            cout << "Tabel Peminjaman"<< endl; 
            cout << "=========================================="<< endl; 
            cout << "Judul Buku\t\t" << "Tanggal Peminjaman"<< endl; 
            cout << "=========================================="<< endl; 
            while(getline(file, line)){
                stringstream ss(line);
                getline(ss, judul, ',');
                getline(ss, tanggal_peminjaman, ',');
                getline(ss, peminjam, ',');

                if (peminjam == userNow)
                {
                    cout << judul << " " << tanggal_peminjaman << " " << peminjam << endl;
                }
            }
            file.close();
            cout << endl;
            system("pause");
            goto label_pilih;
        }break; 
        
        case PENGEMBALIAN: {
            ofstream filePengembalian;
            string buku, pengarang ,line, idBuku;
            filePengembalian.open("data_pengembalian.txt", ios::app);
            ifstream buku_data;

            string kode_buku;
            cout << "Ketik kode buku yang dikembalikan : ";
            cin>> kode_buku;

            buku_data.open("data_buku.txt");
            int i = 0;
            while (!buku_data.eof())
            {
                getline(buku_data, line);
                stringstream ss(line);
                getline(ss, buku, ',');
                getline(ss, pengarang, ',');
                getline(ss, idBuku, ',');

                if (kode_buku == idBuku)
                {
                    filePengembalian << buku << ",";
                    filePengembalian << "\t" << __DATE__ << ",";
                    filePengembalian << lUsername << endl;
                    filePengembalian.close();
                    cout << "Buku " << buku << " | " << pengarang << " Telah Dikembalikan." << endl;
                    buku_data.close();
                    cout << "Tanggal Pengembalian : " << __DATE__ << endl;
                    system("pause");
                    goto label_pilih;
                }
                i++;
            }
            cout << "Buku tidak ditemukan" << endl;
            system("pause");
            goto label_pilih;
        }break; 

        case DAFTARPENGEMBALIAN: {
            string userNow;
            ifstream dataUser("data_mahasiswa.txt");
            while(!dataUser.eof()){
                getline(dataUser, line);
                stringstream ss(line);
                getline(ss, username, ',');
                getline(ss, password, ',');
                getline(ss, nama, ',');
                if (lUsername == username)
                {
                    userNow = username;
                }
            }

            string line;
            ifstream file("data_pengembalian.txt");
            string judul, tanggal_pengembalian, pengembali;
            system("cls");
            cout << "Tabel Pengembalian"<< endl; 
            cout << "=========================================="<< endl; 
            cout << "Judul Buku\t\t" << "Tanggal pengembalian"<< endl; 
            cout << "=========================================="<< endl; 
            while(getline(file, line)){
                stringstream ss(line);
                getline(ss, judul, ',');
                getline(ss, tanggal_pengembalian, ',');
                getline(ss, pengembali, ',');

                if (pengembali == userNow)
                {
                    cout << judul << " " << tanggal_pengembalian << endl;
                }
            }
            file.close();
            cout << endl;
            system("pause");
            goto label_pilih;
        }break; 
        
        default:
            cout << "Masukkan pilihan yang benar" << endl;
            system("pause");
            goto label_pilih;
            break;
        }
    }
    cout << "Terima kasih dan sampai jumpa!" << endl;
    system("pause");
    string *lUsername = NULL;
    string *lPassword = NULL;
    string *nama = NULL;
    system("cls");
    goto HOME;
    cin.get();
    return 0;
}

void login(){
    mahasiswa mhs;
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
    int pilih = 0;
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
    mahasiswa mhs;
    string userNow;
    ifstream dataUser("data_mahasiswa.txt");
    while (!dataUser.eof())
    {
        getline(dataUser, line);
        stringstream ss(line);
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, nama, ',');
        if (lUsername == username)
        {
            mhs.NIM = lUsername;
            mhs.nama = nama;
        }
    }
    system("cls");
    cout << "=======================" << endl;
    cout << "Aplikasi Perpustakaan | " << mhs.nama << endl;
    cout << "=======================" << endl;
    cout << "1. Peminjaman" << endl;
    cout << "2. Daftar Peminjaman" << endl;
    cout << "3. Pengembalian" << endl;
    cout << "4. Daftar Pengembalian" << endl;
    cout << "5. Keluar" << endl;
    cout << "=======================" << endl;
    cout << "Pilih menu: ";
    cin >> pilih;
    return pilih;
}
int menuBuku(){
    int pilih;
    system("cls");
    //manual
    cout << "=======================" << endl;
    cout << "Pilih Buku" << endl;
    cout << "=======================" << endl;
    cout << "0. Cari Buku" << endl;
    cout << "5. Kembali ke laman utama" << endl;
    cout << "=======================" << endl;
    cout << "List Buku" << endl;
    cout << "=======================" << endl;

    ifstream listBuku;
    listBuku.open("data_buku.txt");
    string listJudulBuku, listLineBuku;
    int listNo = 1;

    while (getline(listBuku,listLineBuku))
    {
        stringstream ss(listLineBuku);
        getline(ss, listJudulBuku, ',');
        cout << listNo << ". " << listJudulBuku << endl;
        listNo++;
    }
    
    // cout << "1. Your Name" << endl;
    // cout << "2. Weathering With You" << endl;
    // cout << "3. Re:ZERO" << endl;
    cout << "=======================" << endl;
    cout << "Pilih menu: ";
    cin >> pilih;
    return pilih;
}