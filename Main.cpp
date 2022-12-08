#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>
#include <limits>
#include <stdio.h>
#include <vector>

using namespace std;
struct buku{
    string judul, pengarang, kode, status; 
};

struct mahasiswa{
    string nama, password, NIM; 
};

// Akun Petugas
string petUsername = "admin"; 
string petPassword = "admin"; 
// Active User
string logUsername, username, logPassword, password, nama, line;

int menu();
int menuPetugas();
int menuMahasiswa();
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
        return 0;
    default:
        {
            cout << "Masukan pilihan yang valid" << endl;
            system("pause");
            main();
            break;
        }
    }
    label_pilih:
    int pilih2;
    if (logUsername == petUsername && logPassword == petPassword){
        pilih2 = menuPetugas();
        enum option{KELOLABUKU = 1, DAFTARPEMINJAMAN, DAFTARPENGEMBALIAN, KELUAR};
        while (pilih2 != KELUAR){
            switch (pilih2){
                case KELOLABUKU: {
                    KELOLA_BUKU:
                    int input;
                    string line;
                    ifstream file("data_buku.txt");
                    string judul, pengarang, kodeBuku, status;
                    system("cls");
                    cout << "                  Tabel Buku                  "<< endl; 
                    cout << "=============================================="<< endl; 
                    cout << "Judul Buku\t" << "Pengarang\t"<< "Kode\t" << "Status" << endl; 
                    cout << "=============================================="<< endl; 
                    while(getline(file, line)){
                        stringstream ss(line);
                        getline(ss, judul, ',');
                        getline(ss, pengarang, ',');
                        getline(ss, kodeBuku, ',');
                        getline(ss, status, ',');
                        cout << judul << " " << pengarang << " " << kodeBuku << " " << status << endl;
                    }
                    file.close();
                    cout << "\n "<< endl;
                    cout << "[1] Tambah Buku" << endl;
                    cout << "[2] Hapus Buku" << endl;
                    cout << "Masukkan pilihan: ";
                    cin >> input;
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    switch (input)
                    {
                    case 1:
                        {
                            // CASE TAMBAH BUKU :)
                            buku bk;
                            system("cls");
                            // input data
                            cout << "Masukkan judul buku: ";
                            getline(cin, bk.judul);
                            cout << "Masukkan nama pengarang: ";
                            getline(cin, bk.pengarang);
                            cout << "Masukkan kode buku: ";
                            getline(cin, bk.kode);
                            bk.status = "tersedia";

                            ofstream FileBuku;
                            FileBuku.open("data_buku.txt", ios::app);
                            FileBuku << bk.judul;
                            FileBuku << ",";
                            FileBuku << bk.pengarang;
                            FileBuku << ",";
                            FileBuku << bk.kode;
                            FileBuku << ",";
                            FileBuku << bk.status << endl;
                            FileBuku.close();
                            cout << "Buku berhasil ditambah" << endl;
                            system("pause");
                            goto KELOLA_BUKU;
                        }
                        break;
                    case 2:
                        {
                            // CASE HAPUS BUKU :)
                            string buku, pengarang, kodeBuku, status, line, inputKode;
                            int hapus;
                            cout << "Masukkan kode buku: ";
                            cin >> inputKode;

                            ifstream buku_data;
                            buku_data.open("data_buku.txt");
                            while (!buku_data.eof())
                            {
                                getline(buku_data, line);
                                stringstream ss(line);
                                getline(ss, buku, ',');
                                getline(ss, pengarang, ',');
                                getline(ss, kodeBuku, ',');
                                getline(ss, status, ',');
                                
                                if (inputKode == kodeBuku){
                                    fstream read_file;
                                read_file.open("data_buku.txt");
                                vector<string> lines;
                                string line;

                                while(getline(read_file, line)){
                                    lines.push_back(line);
                                }
                                read_file.close();
                                int line_number = 0;
                                for (int i = 0; i < lines.size(); i++){
                                    if (lines[i] == buku + "," + pengarang + "," + kodeBuku + "," + status){
                                        line_number = i;
                                    };
                                }
                                buku_data.close();
                                ofstream write_file;
                                write_file.open("data_buku.txt");
                                for (int i = 0; i < lines.size(); i++)
                                {
                                    if (i != line_number){
                                        write_file << lines[i] <<endl;
                                        hapus = 1;
                                    }
                                }
                                write_file.close();
                                }
                            }
                            if(hapus == 1){
                                cout << "Data Berhasil Dihapus" << endl;
                                system("pause");
                                goto KELOLA_BUKU;
                            }
                        }
                        break;
                    default:
                        break;
                    }
                }
                break;
                default:
                    break;
                }
        }
        if(pilih2 == KELUAR){
            cout << "Terima kasih dan sampai jumpa!" << endl;
            system("pause");
            string *logUsername = NULL;
            string *logPassword = NULL;
            string *nama = NULL;
            system("cls");
            goto HOME;
            cin.get();
            return 0;
        }
    } else {
        pilih2 = menuMahasiswa();
        enum option{BUKU = 1, PEMINJAMAN, PENGEMBALIAN, DAFTARPENGEMBALIAN, KELUAR};
        // ANCHOR Perubahan buku manual menjadi database
        while(pilih2 != KELUAR){
            switch (pilih2)
            {
            case BUKU: {
                int book_pilih = menuBuku();
                while(book_pilih != 0 && book_pilih != 99){
                    int this_book = book_pilih;
                    ofstream filePeminjaman;
                    ifstream buku_data;
                    string buku, pengarang, kodeBuku, status, line;
                    if (book_pilih == this_book)
                    {
                        int i = 0;
                        filePeminjaman.open("data_peminjaman.txt", ios::app);
                        buku_data.open("data_buku.txt");
                        while (!buku_data.eof())
                        {
                            getline(buku_data, line);
                            stringstream ss(line);
                            getline(ss, buku, ',');
                            getline(ss, pengarang, ',');
                            getline(ss, kodeBuku, ',');
                            getline(ss, status, ',');
                            
                            if (i == this_book - 1)
                            {
                                fstream read_file;
                                read_file.open("data_buku.txt");
                                vector<string> lines;
                                string line;

                                while(getline(read_file, line)){
                                    lines.push_back(line);
                                }
                                read_file.close();
                                int line_number = 0;
                                for (int i = 0; i < lines.size(); i++){
                                    if (lines[i] == buku + "," + pengarang + "," + kodeBuku + "," + status){
                                        line_number = i;
                                    };
                                }
                                ofstream write_file;
                                write_file.open("data_buku.txt");
                                for (int i = 0; i < lines.size(); i++)
                                {
                                    if (i != line_number){
                                        write_file << lines[i] <<endl;
                                    } else {
                                        write_file << buku + "," + pengarang + "," + kodeBuku + "," + "kosong" << endl;
                                    }
                                }
                                write_file.close();
                                if (status == "kosong"){
                                    cout << "Buku sedang dipinjam" << endl;
                                } else if(status == "tersedia"){
                                    filePeminjaman << buku << ",";
                                    filePeminjaman << __DATE__ << ",";
                                    filePeminjaman << logUsername << endl;
                                    filePeminjaman.close();
                                    cout << "Anda telah meminjam buku " << buku << " | " << pengarang << "." << endl;
                                    buku_data.close();
                                    cout << "Tanggal Peminjaman: " << __DATE__ << endl;
                                }
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
                    string buku, pengarang ,kodeBuku, status, line;
                    int i = 0, j = 0;
                    string kotak_judulBuku[10], kotak_idBuku[10], kotak_pengarang[10], kotak_status[10];

                    while (getline(buku_data, line))
                    {
                        stringstream ss(line);
                        getline(ss, buku, ',');
                        getline(ss, pengarang, ',');
                        getline(ss, kodeBuku, ',');
                        getline(ss, status, ',');
                        kotak_judulBuku[i] = buku;
                        kotak_idBuku[i] = kodeBuku;
                        kotak_pengarang[i] = pengarang;
                        kotak_status[i] = status;

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
                            fstream read_file;
                            read_file.open("data_buku.txt");
                            vector<string> lines;
                            string line;

                            while(getline(read_file, line)){
                                lines.push_back(line);
                            }
                            read_file.close();
                            int line_number = 0;
                            for (int i = 0; i < lines.size(); i++){
                                if (lines[i] == kotak_judulBuku[k] + "," + kotak_pengarang[k] + "," + kotak_idBuku[k] + "," + kotak_status[k]){
                                    line_number = i;
                                };
                            }
                            ofstream write_file;
                            write_file.open("data_buku.txt");
                            for (int i = 0; i < lines.size(); i++)
                            {
                                if (i != line_number){
                                    write_file << lines[i] <<endl;
                                } else {
                                    write_file << kotak_judulBuku[k] + "," + kotak_pengarang[k] + "," + kotak_idBuku[k] + "," + "kosong" << endl;
                                }
                            }
                            write_file.close();
                            cout << "Buku " << kotak_judulBuku[k] << " ditemukan" << endl;
                            if (kotak_status[k] == "kosong")
                            {
                                cout << "Buku " << kotak_judulBuku[k] << " sedang dipinjam" << endl;
                                system("pause");
                                goto label_pilih;
                            } else {
                                cout << "Apakah anda ingin meminjam buku tersebut (1/0)? ";
                                cin >> pilih;
                                if (pilih == 1)
                                {
                                ofstream filePeminjaman;
                                filePeminjaman.open("data_peminjaman.txt", ios::app);
                                filePeminjaman << kotak_judulBuku[k] << ",";
                                filePeminjaman << __DATE__ << ",";
                                filePeminjaman << logUsername << endl;
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
                        else {
                            
                        }
                    }
                    cout << "Buku tidak ditemukan"<<endl;
                    system("pause");
                    goto label_pilih;
                } 
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
                    if (logUsername == username)
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
                string buku, pengarang ,line, idBuku, status;
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
                    getline(ss, status, ',');
                    if (kode_buku == idBuku)
                    {
                        fstream read_file;
                        read_file.open("data_buku.txt");
                        vector<string> lines;
                        string line;

                        while(getline(read_file, line)){
                            lines.push_back(line);
                        }
                        read_file.close();
                        int line_number = 0;
                        for (int i = 0; i < lines.size(); i++){
                            if (lines[i] == buku + "," + pengarang + "," + idBuku + "," + status){
                                line_number = i;
                            };
                        }
                        ofstream write_file;
                        write_file.open("data_buku.txt");
                        for (int i = 0; i < lines.size(); i++)
                        {
                            if (i != line_number){
                                write_file << lines[i] <<endl;
                            } else {
                                write_file << buku + "," + pengarang + "," + idBuku + "," + "tersedia" << endl;
                            }
                        }
                        write_file.close();
                        filePengembalian << buku << ",";
                        filePengembalian << "\t" << __DATE__ << ",";
                        filePengembalian << logUsername << endl;
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
                    if (logUsername == username)
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
        if(pilih2 == KELUAR){
            cout << "Terima kasih dan sampai jumpa!" << endl;
            system("pause");
            string *logUsername = NULL;
            string *logPassword = NULL;
            string *nama = NULL;
            system("cls");
            goto HOME;
            cin.get();
            return 0;
        }

    }
}

void login(){
    mahasiswa mhs;
    int count = 0;
    cout << "====================" << endl;
    cout << "Welcome!" << endl;
    cout << "====================" << endl;
    cout << "Username: ";
    cin >> logUsername;
    cout << "Password: ";
    cin >> logPassword;

    if(logUsername == petUsername && logPassword == petPassword){
        count = 1;
        system("cls");
        cout << "\nLogin berhasil!" << endl;
        cout << "\nAnda Login Sebagai Admin" << endl;
        system("pause");
    } else {
        ifstream input("data_mahasiswa.txt");
        while(!input.eof()){
            getline(input, line);
            stringstream ss(line);
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, nama, ',');
            if (username == logUsername && password == logPassword)
            {
                count = 1;
                system("cls");
                cout << "\nLogin berhasil!" << endl;
                cout << "\nAnda Login Sebagai Mahasiswa" << endl;
                system("pause");
                input.close();
            }
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
int menuPetugas(){
    int pilih;
    system("cls");
    cout << "=======================" << endl;
    cout << "Aplikasi Perpustakaan | " << petUsername << endl;
    cout << "=======================" << endl;
    cout << "1. Kelola Buku" << endl;
    cout << "2. Daftar Peminjaman" << endl;
    cout << "3. Daftar Pengembalian" << endl;
    cout << "4. Keluar" << endl;
    cout << "=======================" << endl;
    cout << "Pilih menu: ";
    cin >> pilih;
    return pilih;
}
int menuMahasiswa(){
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
        if (logUsername == username)
        {
            mhs.NIM = logUsername;
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
    cout << "99. Kembali ke laman utama" << endl;
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
    listBuku.close();
    // cout << "1. Your Name" << endl;
    // cout << "2. Weathering With You" << endl;
    // cout << "3. Re:ZERO" << endl;
    cout << "=======================" << endl;
    cout << "Pilih menu: ";
    cin >> pilih;
    return pilih;
}